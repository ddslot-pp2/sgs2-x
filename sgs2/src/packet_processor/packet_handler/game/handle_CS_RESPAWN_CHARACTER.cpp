#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../../../field/field_manager.h"

void handle_CS_RESPAWN_CHARACTER(std::shared_ptr<server_session> session, const GAME::CS_RESPAWN_CHARACTER& read)
{
    auto c = session->get_character();
    if (c)
    {
        auto field_id = c->get_field_id();
        auto field = field_manager::instance().get_field(field_id);
        field->send_task(&field::respawn_character, c->get_object_id());
    }
}
