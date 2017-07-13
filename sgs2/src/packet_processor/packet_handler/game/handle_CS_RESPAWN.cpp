#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"

void handle_CS_RESPAWN(std::shared_ptr<server_session> session, const GAME::CS_RESPAWN& read)
{
    /*
    auto timestamp = read.core::timestamp();
    wprintf(L"timestamp: %lld\n", timestamp);

    GAME::SC_PING send;
    send.set_timestamp(400);

    send_packet(session, opcode::SC_PING, send);
    */
}
