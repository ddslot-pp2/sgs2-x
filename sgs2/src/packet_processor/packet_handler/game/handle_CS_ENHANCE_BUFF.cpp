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

    wprintf(L"버프 증가 초이스: %d\n", read.buff_type());

    auto stat_info = c->get_stat_info();

    if (stat_info->enhance_buff_count <= 0)
    {
        wprintf(L"버프 증가 할수없음\n");
        return;
    }

    auto enhance_buff_count = stat_info->enhance_buff_count - 1;
    stat_info->enhance_buff_count = std::max(0, enhance_buff_count);

    wprintf(L"버프 증가 카운트: %d\n", stat_info->enhance_buff_count);
   
    auto type = read.buff_type();
    if (type == to_index(buff_type::max_hp))
    {
        auto max_hp_per = stat_info->max_hp * 0.1f;
        wprintf(L"before 최대 hp: %d\n", stat_info->max_hp.load());
        stat_info->max_hp = stat_info->max_hp + max_hp_per;
        wprintf(L"after  최대 hp: %d\n", stat_info->max_hp.load());
    }
    else if (type == to_index(buff_type::character_speed))
    {
        auto speed_per = stat_info->speed * 0.1f;
        wprintf(L"before 스피드: %f\n", stat_info->speed.load());
        stat_info->speed = stat_info->speed + speed_per;
        wprintf(L"after  스피드: %f\n", stat_info->speed.load());
    }
    else if (type == to_index(buff_type::bullet_speed))
    {
        auto bullet_speed_per = stat_info->bullet_speed * 0.1f;
        wprintf(L"before 총알 스피드: %f\n", stat_info->bullet_speed.load());
        stat_info->bullet_speed = stat_info->bullet_speed + bullet_speed_per;
        wprintf(L"after  총알 스피드: %f\n", stat_info->bullet_speed.load());
    }
    else if (type == to_index(buff_type::bullet_power))
    {
        auto bullet_power_per = stat_info->bullet_power * 0.1f;
        wprintf(L"before 총알 파워: %f\n", stat_info->bullet_power.load());
        stat_info->bullet_power = stat_info->bullet_power + bullet_power_per;
        wprintf(L"after  총알 파워: %f\n", stat_info->bullet_power.load());
    }
    else if (type == to_index(buff_type::bullet_distance))
    {
        auto bullet_distance_per = stat_info->bullet_distance * 0.1f;
        wprintf(L"before 총알 사정거리: %f\n", stat_info->bullet_distance.load());
        stat_info->bullet_distance = stat_info->bullet_distance + bullet_distance_per;
        wprintf(L"before 총알 사정거리: %f\n", stat_info->bullet_distance.load());
    }
    else if (type == to_index(buff_type::reload_time))
    {
        auto reload_time_per = stat_info->reload_time * 0.1f;
        wprintf(L"before 리로드 시간: %f\n", stat_info->reload_time.load());
        stat_info->reload_time = stat_info->reload_time - reload_time_per;
        wprintf(L"after  리로드 시간: %f\n", stat_info->reload_time.load());
    }

    if (type == to_index(buff_type::bullet_speed) || type == to_index(buff_type::bullet_power) || type == to_index(buff_type::bullet_distance)) return;

    if (type == to_index(buff_type::reload_time))
    {
        GAME::SC_NOTI_UPDATE_CHARACTER_STATUS noti;
        noti.set_obj_id(c->get_object_id());
        noti.set_max_hp(stat_info->max_hp);
        noti.set_hp(stat_info->hp);
        noti.set_speed(stat_info->speed);
        noti.set_reload_time(stat_info->reload_time);
        send_packet(session, opcode::SC_NOTI_UPDATE_CHARACTER_STATUS, noti);
        return;
    }
    
    auto field_id = c->get_field_id();
    auto field = field_manager::instance().get_field(field_id);
    field->send_task(&field::update_character_status, c->get_object_id());
}
