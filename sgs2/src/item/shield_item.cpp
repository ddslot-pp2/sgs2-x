#include "shield_item.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/opcode.h"
#include "../packet_processor/send_helper.h"

shield_item::shield_item(field_id id, std::chrono::milliseconds reactive_time, const vector3& pos) : item(id, reactive_time, pos)
{
    wprintf(L"shield 아이템 생성\n");
    type_ = item::type::shield;
}

shield_item::~shield_item()
{

}

void shield_item::update(float delta)
{
    if (!active_) return;

    for (auto& kv : field_->get_view_list())
    {
        auto c = kv.second;

        auto stat_info = c->get_stat_info();

        if (check_intersection(c->get_pos(), stat_info->size))
        {
            wprintf(L"유저가 shield 아이템 획득\n");

            // 로직처리
            c->start_shield_timer(std::chrono::milliseconds(1000 * 10));

            noti_acquire_item(c, stat_info);

            active_ = false;

            auto self = shared_from_this();
            active_timer_->expires_from_now(reactive_time_);
            active_timer_->async_wait([this, self](const boost::system::error_code& ec) {

                if (ec)
                {
                    //if(ec == boost::system::error_code::operation_canceled
                    wprintf(L"shield_item 타이머가 문제있음\n");
                    return;
                }

                active_ = true;
                field_->noti_active_item(item_id_, to_integral(type_), pos_);
            });

            return;
        }
    }
}

void shield_item::noti_acquire_item(std::shared_ptr<character> c, std::shared_ptr<stat_info> stat_info) const
{
    GAME::SC_NOTI_ACQUIRE_ITEM noti;
    noti.set_obj_id(c->get_object_id());
    noti.set_item_id(item_id_);
    noti.set_item_type(to_integral(item::type::shield));
    noti.set_hp(stat_info->hp);
    noti.set_shield_time(c->get_shield_time());

    for (const auto& kv : field_->get_view_list())
    {
        auto other = kv.second;

        auto other_session = other->get_session();
        if (!other_session) continue;

        send_packet(other_session, opcode::SC_NOTI_ACQUIRE_ITEM, noti);
    }
}
