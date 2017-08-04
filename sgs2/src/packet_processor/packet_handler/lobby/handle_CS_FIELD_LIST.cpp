#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../core/src/locale/string_helper.h"

void handle_CS_FIELD_LIST(std::shared_ptr<server_session> session, const LOBBY::CS_FIELD_LIST& read)
{
    auto error_handler = [session]
    {
        LOBBY::SC_LOG_IN send;
        send.set_result(false);
        send_packet(session, opcode::SC_LOG_IN, send);
        session->close();
    };

    
}
