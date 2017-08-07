#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"

void handle_CS_PING(std::shared_ptr<server_session> session, const GAME::CS_PING& read)
{
    session->set_ping(true);
    /*
    auto timestamp = read.timestamp();
    wprintf(L"timestamp: %lld\n", timestamp);

    GAME::SC_PING send;
    send.set_timestamp(400);
    */

    //send_packet(session, opcode::SC_PING, send);
}
