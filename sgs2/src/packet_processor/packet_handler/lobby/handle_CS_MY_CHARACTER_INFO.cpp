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

void handle_CS_MY_CHARACTER_INFO(std::shared_ptr<server_session> session, const LOBBY::CS_MY_CHARACTER_INFO& read)
{
    auto error_handler = [session] (std::string ec) {
        LOBBY::SC_MY_CHARACTER_INFO send;
    
        send_packet(session, opcode::SC_MY_CHARACTER_INFO, send);
        session->close();
    };

    auto acc = session->get_account();

    if (!acc)  {
        error_handler("invalid account");
        return;
    }

    using namespace mysql_connector;

    auto q = make_query("sp_get_all_character_info", acc->get_account_id());
    auto res = execute_query(q);
    //auto res = execute_query("call sp_get_add_user_info('adfsfwefwef2', '1111', 'aa', 1);");

    if (!res) {
        error_handler("error sp_get_all_character_info query");
        return;
    }

    LOBBY::SC_MY_CHARACTER_INFO send;
    send.set_result(true);
    send.set_ec("");

    while (res->next()) {
        auto character_info = send.add_character_infos();
        character_info->set_type(res->getUInt("character_type"));
        character_info->set_max_hp(res->getUInt("max_hp"));
        character_info->set_speed(res->getUInt("speed"));
        character_info->set_bullet_speed(res->getUInt("bullet_speed"));
        character_info->set_bullet_power(res->getUInt("bullet_power"));
        character_info->set_bullet_distance(res->getUInt("bullet_distance"));
        character_info->set_reload_time(res->getUInt("reload_time"));
    }

    send_packet(session, opcode::SC_MY_CHARACTER_INFO, send);
}
