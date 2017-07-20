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

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

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

void test()
{
    tcp::socket sock(network::io_service());
    auto sess = std::make_shared<server_session>(std::move(sock));
    auto fid = 0;

    field_manager::instance().try_enter_field(fid, sess);


    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    auto c = sess->get_character();
    if (c)
    {
        c->send_task<move_component>(comp_id::move_comp, &move_component::say_hello);
    
        std::this_thread::sleep_for(2s);
        //sess->destroy_character();
    }
}

void test_sql()
{
    using namespace std;

    try 
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "1111");
        /* Connect to the MySQL test database */
        con->setSchema("test");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
        while (res->next()) {
            cout << "\t... MySQL replies: ";
            /* Access column data by alias or column name */
            cout << res->getString("_message") << endl;
            cout << "\t... MySQL says it again: ";
            /* Access column data by numeric offset, 1 is the first column */
            cout << res->getString(1) << endl;
        }
        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    //return EXIT_SUCCESS;
}

void on_local_thread_initialize()
{

}

int main()
{
    test_sql();
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
    // 테스트
    //network::io_service().post(test);

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
