#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../../../field/field_manager.h"

void handle_CS_SYNC_FIELD(std::shared_ptr<server_session> session, const GAME::CS_SYNC_FIELD& read)
{
    // 댕글릴 될수 있음 atomic_load가 아니라서 봅시다...
    auto c = session->get_character();
    if (c)
    {
        auto field_id = c->get_field_id();
        auto field = field_manager::instance().get_field(field_id);
        field->send_task(&field::sync_field, session);
    }
    //GAME::SC_SYNC_FIELD send;
    //send_packet(session, opcode::SC_SYNC_FIELD, send);
}
