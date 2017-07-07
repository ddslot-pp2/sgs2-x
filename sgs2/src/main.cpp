#include <iostream>
#include "server/server.h"
#include "io_helper.h"
#include "server_session/server_session.h"
#include "packet_processor/packet_processor.h"
#include <csignal>

std::mutex m;
std::condition_variable cv;
std::atomic_bool stop = false;

void sig_handler(int signal_val)
{
    //std::sig_atomic_t v = signal_val;
    stop = true;
    cv.notify_all();
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
    network::initialize();

    // 서버 생성
    tcp::endpoint endpoint(tcp::v4(), 3000);
    auto svr = std::make_unique<network::server<server_session>>(network::io_service(), endpoint);

    //network::start(8, [] {});
    const auto num_cpus = std::thread::hardware_concurrency();
    network::start(num_cpus);

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
