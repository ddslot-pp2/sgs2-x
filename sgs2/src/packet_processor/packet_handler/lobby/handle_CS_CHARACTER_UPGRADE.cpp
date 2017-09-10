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

void handle_CS_CHARACTER_UPGRADE(std::shared_ptr<server_session> session, const LOBBY::CS_CHARACTER_UPGRADE& read)
{
    auto error_handler = [session] (std::string ec)
    {
        LOBBY::SC_CHARACTER_UPGRADE send;
    
        send_packet(session, opcode::SC_CHARACTER_UPGRADE, send);
        session->close();
    };

    auto acc = session->get_account();

    if (!acc) 
    {
        error_handler("invalid account");
        return;
    }


    LOBBY::SC_CHARACTER_UPGRADE send;
    send.set_result(true);
    send.set_ec("");

    send_packet(session, opcode::SC_CHARACTER_UPGRADE, send);
}
