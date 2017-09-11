#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../../../mysql/query_helper.h"
#include "../../../mysql/mysql_connector.h"

void handle_CS_CHARACTER_SELECT(std::shared_ptr<server_session> session, const LOBBY::CS_CHARACTER_SELECT& read)
{
    auto error_handler = [session] (std::string ec)
    {
        LOBBY::CS_CHARACTER_SELECT send;
    
        send_packet(session, opcode::SC_CHARACTER_SELECT, send);
        session->close();
    };

    auto acc = session->get_account();

    if (!acc) {

        return;
    }

    wprintf(L"케릭터 SELECT 패킷 요청 받음");

    auto select_type = read.type();

    // TODO: select_type 예외처리
    session->set_character_type(select_type);
    auto q = make_query("sp_update_account_info", acc->get_account_id(), acc->get_medal_count(), acc->get_coin_count(), session->get_character_type());
    mysql_connector::execute(q);

    LOBBY::SC_CHARACTER_SELECT send;
    send.set_result(true);
    send.set_ec("");

    send_packet(session, opcode::SC_CHARACTER_SELECT, send);
}
