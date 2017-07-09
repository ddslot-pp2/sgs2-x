#include <iostream>
#include "server/server.h"
#include "io_helper.h"
#include "server_session/server_session.h"
#include "packet_processor/packet_processor.h"
#include <csignal>
#include <boost/variant.hpp>
#include <queue>
#include <type_traits>   
#include "../../core/src/timer/timer_helper.hpp"
#include "field/field_manager.h"

std::mutex m;
std::condition_variable cv;
std::atomic_bool stop = false;

void sig_handler(int signal_val)
{
    //std::sig_atomic_t v = signal_val;
    stop = true;
    cv.notify_all();
}

void initialize()
{
    // 필드 생성
    field_manager::instance().create_fields();

    // 필드 업데이트 시작 
    field_manager::instance().update_fields();

}

/*
void update_all_field()
{
    while (true)
    {
        for (auto field : fields)
        {
            using namespace network;
            if (field->check_update_flag())
            {
                
                io_service().post([field] {
                    field->try_update();
                });
            }
            
        }
    }
}
*/

void on_local_thread_initialize()
{

}

int main()
{
    // 서버 종료 ctrl + break
    std::signal(SIGBREAK, sig_handler);

    // 로케일 설정
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));

    // 패킷 등록
    register_handlers();

    // io_service 생성 및 네트워크 초기화
    network::initialize();

    // 메인 스레드 초기화
    initialize();
    //network::io_service().post(update_all_field);

    // 서버 생성
    tcp::endpoint endpoint(tcp::v4(), 3000);
    auto svr = std::make_unique<network::server<server_session>>(network::io_service(), endpoint);

    // io 스레드 런하기 전에 io_service 필요한 이벤트들을 등록
    const auto num_cpus = std::thread::hardware_concurrency();
    network::start(num_cpus, on_local_thread_initialize);

    std::unique_lock<std::mutex> lk(m);

    cv.wait(lk, []
    {
        if (stop)
        {
            wprintf(L"서버 종료 알림\n");
            return true;
        }

        wprintf(L"메인 스레드 대기\n");
        return false;
    });

    wprintf(L"서버 종료 시작\n");
    network::stop();

    return 0;
}
