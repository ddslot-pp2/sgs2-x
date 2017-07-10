#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../../../field/field_manager.h"

void handle_CS_NOTI_MOVE(std::shared_ptr<server_session> session, const GAME::CS_NOTI_MOVE& read)
{
    // 댕글릴 될수 있음 atomic_load가 아니라서 봅시다...
    auto c = session->get_character();
    if (c)
    {
        vector3 pos(read.pos_x(), read.pos_y(), read.pos_z());
        c->send_task<move_component>(comp_id::move_comp, &move_component::set_pos, pos);
        //auto field_id = c->get_field_id();
        //auto field = field_manager::instance().get_field(field_id);
        //field->send_task(&field::sync_field, session);
    }
    //GAME::SC_SYNC_FIELD send;
    //send_packet(session, opcode::SC_SYNC_FIELD, send);
}
