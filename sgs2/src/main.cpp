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
    // ���� ���� ctrl + break
    std::signal(SIGBREAK, sig_handler);

    // ������ ����
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));

    // ��Ŷ ���
    register_handlers();
    network::initialize();

    // ���� ����
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
            wprintf(L"���� ���� �˸�\n");
            return true;
        }
        
        wprintf(L"���� ������ ���\n");
        return false;
    });
    
    wprintf(L"���� ���� ����\n");
    network::stop();

    return 0;
}
