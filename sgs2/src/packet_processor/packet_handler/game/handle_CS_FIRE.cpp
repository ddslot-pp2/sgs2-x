#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../../../field/field_manager.h"

void handle_CS_FIRE(std::shared_ptr<server_session> session, const GAME::CS_FIRE& read)
{
    // ��۸� �ɼ� ���� atomic_load�� �ƴ϶� ���ô�...
    auto c = session->get_character();
    if (c)
    {
        vector3 pos(read.pos_x(), read.pos_y(), read.pos_z());
        vector3 dir(read.dir_x(), read.dir_y(), read.dir_z());

        for (auto i=0; i<read.bullet_infos_size(); ++i)
        {
            auto& bullet_info = read.bullet_infos(i);
            vector3 bullet_dir(bullet_info.dir_x(), bullet_info.dir_y(), bullet_info.dir_z());
            
            c->send_task<skill_component>(comp_id::skill_comp, &skill_component::fire, bullet::int_to_type(read.bullet_type()), pos, dir, bullet_dir);
        }
    }
}