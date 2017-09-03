#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../core/src/locale/string_helper.h"
#include "../../../field/field_manager.h"
#include "../../../property/property_manager.h"
#include "../../../mysql/mysql_connector.h"
#include "../../../mysql/query_helper.h"

void handle_CS_PURCHASE_CHARACTER(std::shared_ptr<server_session> session, const LOBBY::CS_PURCHASE_CHARACTER& read)
{
    auto error_handler = [session] (std::string error_code)
    {
        LOBBY::SC_PURCHASE_CHARACTER send;
        send.set_result(false);
        send.set_ec(error_code);
        send_packet(session, opcode::SC_PURCHASE_CHARACTER, send);
    };

    auto character_type = read.character_type();

    auto acc = session->get_account();
    if (!acc) return;

    auto medal_count = acc->get_medal_count();
    
    auto req_medal_count = property_manager::instance().get_default_character_medal_info(character_type);

    if (req_medal_count <= 0)
    {
        error_handler("not exist tank_type! should be range from 0 to 9");
        return;
    }

    // 현재 유저가 소유한 메달보다 많이 필요하다면
    if (req_medal_count > medal_count)
    {
        error_handler("not enough medal");
        return;
    }

    using namespace mysql_connector;

    // db 요청 추가 능력치 가져오기
    auto acc_id = acc->get_account_id();

    auto q = make_query("sp_add_character_info", acc_id, character_type);
    auto res = execute_query(q);
    //auto res = execute_query("call sp_get_add_user_info('adfsfwefwef2', '1111', 'aa', 1);");

    if (!res)
    {
        error_handler("query failure");
        return;
    }

    while (res->next())
    {
        auto r = res->getUInt("success");
        if (!r)
        {
            error_handler("has owned character");
            return;
        }
    }

    wprintf(L"케릭터 구매 성공\n");
    acc->dec_medal_count(req_medal_count);
    
    session->set_character_type(character_type);
    q = make_query("sp_update_account_info", acc_id, acc->get_medal_count(), acc->get_coin_count(), session->get_character_type());
    execute(q);

    q = make_query("sp_get_character_info", acc_id, character_type);
    res = execute_query(q);
    if (!res)
    {
        error_handler("fail to get character_info");
        return;
    }

    while (res->next())
    {
        // 추가 능력치이며 character_type의 의해 결정됨
        stat_info stat;
        stat.max_hp = res->getUInt("max_hp");
        stat.speed = static_cast<float>(res->getUInt("speed"));
        stat.bullet_speed = static_cast<float>(res->getUInt("bullet_speed"));
        stat.bullet_power = static_cast<float>(res->getUInt("bullet_power"));
        stat.bullet_distance = static_cast<float>(res->getUInt("bullet_distance"));
        stat.reload_time = static_cast<float>(res->getUInt("reload_time"));

        session->set_stat_info(stat);
    }

    // 구매 결과값을 전달
    LOBBY::SC_PURCHASE_CHARACTER send;
    send.set_result(true);
    send.set_medal_count(acc->get_medal_count());
    send.set_coin_count(acc->get_coin_count());
    send.set_ec("");

    send_packet(session, opcode::SC_PURCHASE_CHARACTER, send);
}
