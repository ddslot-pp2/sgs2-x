#include "../../packet_processor.h"
#include <memory>
#include "../../../server_session/server_session.h"
#include "../../opcode.h"
#include "../../send_helper.h"
#include "../../../field/field_manager.h"

void handle_CS_ENHANCE_BUFF(std::shared_ptr<server_session> session, const GAME::CS_ENHANCE_BUFF& read)
{
    // 댕글릴 될수 있음 atomic_load가 아니라서 봅시다...
    auto c = session->get_character();
    if (!c) return;
    
    static const auto to_index = [] (buff_type type) {
        return static_cast<std::underlying_type<buff_type>::type>(type);
    };

    auto stat_info = c->get_stat_info();

    if (stat_info->enhance_buff_count <= 0) return;
   
    auto type = read.buff_type();
    if (type == to_index(buff_type::max_hp))
    {
        stat_info->max_hp = stat_info->max_hp + 10;
    }
    else if (type == to_index(buff_type::character_speed))
    {
        stat_info->speed = stat_info->speed + 2.0f;
    }
    else if (type == to_index(buff_type::bullet_speed))
    {
        stat_info->bullet_speed = stat_info->bullet_speed + 4.0f;
    }
    else if (type == to_index(buff_type::bullet_power))
    {
        stat_info->bullet_power = stat_info->bullet_power + 2.0f;
    }
    else if (type == to_index(buff_type::bullet_distance))
    {
        stat_info->bullet_distance = stat_info->bullet_distance + 4.0f;
    }
    else if (type == to_index(buff_type::reload_time))
    {
        stat_info->reload_time = stat_info->reload_time - 50.0f;
    }

    auto enhance_buff_count = stat_info->enhance_buff_count - 1;
    stat_info->enhance_buff_count = std::max(0, enhance_buff_count);

    auto field_id = c->get_field_id();
    auto field = field_manager::instance().get_field(field_id);
    field->send_task(&field::update_character_status, c->get_object_id());
}
