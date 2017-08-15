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

void handle_CS_CHARACTER_INFO(std::shared_ptr<server_session> session, const LOBBY::CS_CHARACTER_INFO& read)
{
    auto acc_id = session->get_account_id();
    if (acc_id <= 0) return;

    auto character_type = read.character_type();

    using namespace mysql_connector;
 
    auto q = make_query("sp_get_character_info", acc_id, character_type);
    auto res = execute_query(q);
    if (!res)
    {
        return;
    }

    LOBBY::SC_CHARACTER_INFO send;
    send.set_result(true);

    while (res->next())
    {
        send.set_max_hp(res->getUInt("max_hp"));
        send.set_speed(res->getUInt("speed"));
        send.set_bullet_speed(res->getUInt("bullet_speed"));
        send.set_bullet_power(res->getUInt("bullet_power"));
        send.set_bullet_distance(res->getUInt("bullet_distance"));
        send.set_reload_time(res->getUInt("reload_time"));
    }

    //  결과값을 전달
    send_packet(session, opcode::SC_CHARACTER_INFO, send);
}
