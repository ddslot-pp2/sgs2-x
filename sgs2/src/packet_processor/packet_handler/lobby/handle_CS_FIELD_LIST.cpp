#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../core/src/locale/string_helper.h"

void handle_CS_FIELD_LIST(std::shared_ptr<server_session> session, const LOBBY::CS_FIELD_LIST& read)
{
    LOBBY::SC_FIELD_LIST send;
    send.set_result(true);

    for (auto i = 0; i < 2; ++i)
    {
        auto field = send.add_field_infos();
        field->set_field_id(i);
        field->set_user_count(i+10);
        field->set_max_user_count(50);
    }

    send_packet(session, opcode::SC_FIELD_LIST, send);
}
