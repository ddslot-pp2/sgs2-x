#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../core/src/locale/string_helper.h"
#include "../../../account/account_manager.h"
#include <random>
#include "../../../../../core/src/timer/timer_helper.hpp"
#include "../../../mysql/mysql_connector.h"
#include "../../../mysql/query_helper.h"

void handle_CS_LOG_IN(std::shared_ptr<server_session> session, const LOBBY::CS_LOG_IN& read)
{
    auto error_handler = [session]
    {
        LOBBY::SC_LOG_IN send;
        send.set_result(false);
        send_packet(session, opcode::SC_LOG_IN, send);
        session->close();
    };

    auto id = core::utf8_to_wstring(read.id());
    wprintf(L"id: %s\n", id.c_str());

    auto password = core::utf8_to_wstring(read.password());
    wprintf(L"password: %s\n", password.c_str());

    auto error_message = "";
    auto result = true;
    //auto nickname = L"돌격탱크" + std::to_wstring(dist_id);

    // db에 요청해서 유저 정보 가져옴 없으면 생성후 가져옴
    // call sp_get_user_info(uuid, password, login_type)
    using namespace mysql_connector;
    
    auto q = make_query("sp_get_add_account_info", read.id(), "1111", 1);
    auto res = execute_query(q);
    //auto res = execute_query("call sp_get_add_user_info('adfsfwefwef2', '1111', 'aa', 1);");

    if (!res)
    {
        error_handler();
        return;
    }
   
    account_info acc_info;
    auto character_type = 1;
    
    while (res->next())
    {
        auto uid = res->getUInt64("uid");
        acc_info.id = uid;
        acc_info.medal_count = res->getUInt("medal_count");
        acc_info.coin_count  = res->getUInt("coin_count");
        acc_info.nickname = core::utf8_to_wstring(res->getString("nickname"));
        if (acc_info.nickname == L"")
        {
            acc_info.nickname = L"게스트" + std::to_wstring(acc_info.id);
        }

        character_type = res->getUInt("character_type");
    }

    auto acc = account_manager::instance().add_account(acc_info);
    if (!acc)
    {
        error_handler();
        return;
    }

    session->set_character_type(character_type);
    session->set_account(acc);

    // 추가 능력치이며 character_type의 의해 결정됨
    stat_info stat;
    stat.max_hp = 0;
    stat.speed  = 0;
    stat.bullet_speed = 0.0f;
    stat.bullet_power = 0.0f;
    stat.bullet_distance = 0.0f;
    stat.reload_time = 0.0f;

    session->set_stat_info(stat);

    // 로그인 결과값을 전달
    LOBBY::SC_LOG_IN send;
    send.set_result(result);
    send.set_timestamp(core::timestamp().count());
    send.set_nickname(core::wstring_to_utf8(acc->get_nickname()));

    send.set_medal_count(acc->get_medal_count());
    send.set_coin_count(acc->get_coin_count());

    send_packet(session, opcode::SC_LOG_IN, send);

    /*
    std::vector<std::thread> v;
    for (auto thread_count = 0; thread_count < 4; ++thread_count)
    {
        v.emplace_back([session, send] {
            for (auto i = 0; i < 5; ++i)
            {
                //wprintf(L"패킷 보냄: %d\n", i);
                send_packet(session, opcode::SC_LOG_IN, send);
            }
        });
    }

    for (auto& t : v)
    {
        t.join();
    }
    */
    
}
