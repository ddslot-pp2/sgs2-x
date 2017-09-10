#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"

void handle_CS_CHARACTER_SELECT(std::shared_ptr<server_session> session, const LOBBY::CS_CHARACTER_SELECT& read)
{
    auto error_handler = [session] (std::string ec)
    {
        LOBBY::CS_CHARACTER_SELECT send;
    
        send_packet(session, opcode::SC_CHARACTER_SELECT, send);
        session->close();
    };

    

    LOBBY::SC_CHARACTER_SELECT send;
    send.set_result(true);
    send.set_ec("");


    send_packet(session, opcode::SC_CHARACTER_SELECT, send);
}
