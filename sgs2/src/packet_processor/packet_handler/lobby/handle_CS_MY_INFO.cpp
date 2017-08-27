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

void handle_CS_MY_INFO(std::shared_ptr<server_session> session, const LOBBY::CS_MY_INFO& read)
{
    auto error_handler = [session] (std::string ec)
    {
        LOBBY::SC_MY_INFO send;
        send.set_result(false);
        send.set_ec(ec);
        send_packet(session, opcode::SC_MY_INFO, send);
        session->close();
    };

    auto acc = session->get_account();

    if (!acc) 
    {
        error_handler("invalid account");
        return;
    }

    const auto medal_count = acc->get_medal_count();
    const auto coin_count  = acc->get_coin_count();

    LOBBY::SC_MY_INFO send;
    send.set_result(true);
    send.set_ec("");
    send.set_medal_count(medal_count);
    send.set_coin_count(coin_count);

    send_packet(session, opcode::SC_MY_INFO, send);
}
