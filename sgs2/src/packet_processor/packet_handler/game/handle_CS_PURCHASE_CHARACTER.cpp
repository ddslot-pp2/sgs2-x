#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../core/src/locale/string_helper.h"
#include "../../../field/field_manager.h"

void handle_CS_PURCHASE_CHARACTER(std::shared_ptr<server_session> session, const LOBBY::CS_ENTER_FIELD& read)
{
    auto field_id = read.field_id();
    field_manager::instance().try_enter_field(field_id, session);
}
