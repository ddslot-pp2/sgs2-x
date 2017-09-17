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

    // ���� ������ ������ �޴޺��� ���� �ʿ��ϴٸ�
    if (req_medal_count > medal_count)
    {
        error_handler("not enough medal");
        return;
    }

    using namespace mysql_connector;

    // db ��û �߰� �ɷ�ġ ��������
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

    wprintf(L"�ɸ��� ���� ����\n");
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
        // �߰� �ɷ�ġ�̸� character_type�� ���� ������
        CharacterLevelInfo level_info;
        level_info.max_hp_level = res->getUInt("max_hp");
        level_info.speed_level = res->getUInt("speed");
        level_info.bullet_speed_level = res->getUInt("bullet_speed");
        level_info.bullet_power_level = res->getUInt("bullet_power");
        level_info.bullet_distance_level = res->getUInt("bullet_distance");
        level_info.reload_time_level = res->getUInt("reload_time");

        auto stat = property_manager::instance().CharacterStatByLevel(character_type, level_info);
        if (!stat) {
            // error
            return;
        }

        session->set_stat_info(*stat);
    }

    // ���� ������� ����
    LOBBY::SC_PURCHASE_CHARACTER send;
    send.set_result(true);
    send.set_medal_count(acc->get_medal_count());
    send.set_coin_count(acc->get_coin_count());
    send.set_ec("");

    send_packet(session, opcode::SC_PURCHASE_CHARACTER, send);
}
