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
#include "../../core/src/locale/string_helper.h"
#include "mysql/mysql_connector.h"
#include "property/property_manager.h"
#include "rank/rank_info.h"
#include "exception.hpp"
#include <boost/property_tree/xml_parser.hpp>

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
    // �ʵ� ����
    field_manager::instance().create_fields();

    // �ʵ� ������Ʈ ���� 
    field_manager::instance().update_fields();

    // �⺻ property �б�
    property_manager::instance().read_xml(L"");
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

bool connect_to_mysql()
{
    using namespace mysql_connector;

    try
    {
        make_connection(L"aurora.cqgzbcd3tarw.ap-northeast-2.rds.amazonaws.com", 3306, L"root", L"11111111", L"aurora");
        wprintf(L"sql ���� ����\n");
        return true;
    }
    catch (sql::SQLException &e) 
    {
        auto e_what = e.what();
        printf("error: %s\n", e_what);
        return false;
        //cout << " (MySQL error code: " << e.getErrorCode();
        //cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void on_local_thread_initialize()
{
    assert(connect_to_mysql(), "unable to connect to mysql server!");
}

int main()
{
    // data �Ľ�
    try {
        property_manager::instance().load_character_stat("./character_stat.xml");
        property_manager::instance().to_print_stat();
    } catch (boost::property_tree::xml_parser::xml_parser_error e) {
        printf("what: %s", e.what());
    }

    //getchar();

    // ���� ���� ctrl + break
    std::signal(SIGBREAK, sig_handler);

    // ������ ����
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));

    // ��Ŷ ���
    register_handlers();

    // io_service ���� �� ��Ʈ��ũ �ʱ�ȭ
    network::initialize();

    // ���� ������ �ʱ�ȭ
    initialize();
    //network::io_service().post(update_all_field);
    // �׽�Ʈ
    //network::io_service().post(test);

    // ���� ����
    tcp::endpoint endpoint(tcp::v4(), 3000);
    auto svr = std::make_unique<network::server<server_session>>(network::io_service(), endpoint);

    // io ������ ���ϱ� ���� io_service �ʿ��� �̺�Ʈ���� ���
    const auto num_cpus = std::thread::hardware_concurrency();
    network::start(num_cpus, on_local_thread_initialize);

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
