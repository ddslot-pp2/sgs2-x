#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../core/src/locale/string_helper.h"
#include "../../../account/account_manager.h"
#include <random>
#include "../../../../../core/src/timer/timer_helper.hpp"

void handle_CS_LOG_IN(std::shared_ptr<server_session> session, const LOBBY::CS_LOG_IN& read)
{
    auto id = core::utf8_to_wstring(read.id());
    wprintf(L"id: %s\n", id.c_str());

    auto password = core::utf8_to_wstring(read.password());
    wprintf(L"password: %s\n", password.c_str());

    auto error_message = "";
    auto result = true;

    // id 와 password 기준으로 유저의 account_id를 가져옴
    // 임시 account id 값 생성 
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10000); 

    auto account_id = dist(rng);

    // 어카운트 매니져에 어카운트 추가
    account_info acc_info;
    acc_info.id = account_id;
    acc_info.medal_count = 150;
    acc_info.coin_count = 500;

    auto nickname = L"돌격탱크" + std::to_wstring(account_id);

    acc_info.nickname = nickname;

    auto acc = account_manager::instance().add_account(acc_info);
    if (!acc)
    {
        LOBBY::SC_LOG_IN send;
        send.set_result(false);
        send_packet(session, opcode::SC_LOG_IN, send);
        return;
    }

    auto character_type = 1;
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
