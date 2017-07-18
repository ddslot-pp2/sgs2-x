#include "hp_item.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/opcode.h"
#include "../packet_processor/send_helper.h"

hp_item::hp_item(field_id id, std::chrono::milliseconds reactive_time, const vector3& pos) : item(id, reactive_time, pos)
{
    wprintf(L"hp 아이템 생성\n");
    type_ = item::type::hp;
}

hp_item::~hp_item()
{

}

void hp_item::update(float delta)
{
    if (!active_) return;

    for (auto& kv : field_->get_view_list())
    {
        auto object_ = kv.second;

        auto stat_info = object_->get_stat_info();

        if (check_intersection(object_->get_pos(), stat_info->size))
        {
            wprintf(L"유저가 hp 아이템 획득\n");

            stat_info->hp += 10;

            auto hp = std::max(stat_info->max_hp.load(), stat_info->hp.load());
            stat_info->hp = hp;
            
            // 유저 아이템 효과 적용된 정보를 업데이트
            //field_->send_task(&field::update_character_status, kv.first);
            noti_acquire_item(kv.first, stat_info);

            active_ = false;

            auto self = shared_from_this();
            active_timer_->expires_from_now(reactive_time_);
            active_timer_->async_wait([this, self] (const boost::system::error_code& ec) {

                if (ec)
                {
                    //if(ec == boost::system::error_code::operation_canceled
                    wprintf(L"hp_item 타이머가 문제있음\n");
                    return;
                }

                active_ = true;
                field_->noti_active_item();
            });

            return;
        }
    }
    //check_intersection(
}

void hp_item::noti_acquire_item(object_id id, std::shared_ptr<stat_info> stat_info) const
{
    
    GAME::SC_NOTI_ACQUIRE_ITEM noti;
    noti.set_obj_id(id);
    noti.set_item_id(item_id_);
    noti.set_item_type(to_integral(item::type::hp));
    noti.set_hp(stat_info->hp);

    for (const auto& kv : field_->get_view_list())
    {
        auto other = kv.second;

        auto other_session = other->get_session();
        if (!other_session) continue;

        send_packet(other_session, opcode::SC_NOTI_ACQUIRE_ITEM, noti);
    }
}
