#include "coin_item.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/opcode.h"
#include "../packet_processor/send_helper.h"

coin_item::coin_item(field_id id, std::chrono::milliseconds reactive_time, const vector3& pos) : item(id, reactive_time, pos)
{
    wprintf(L"coin 아이템 생성\n");
    type_ = item::type::coin;
}

coin_item::~coin_item()
{

}

void coin_item::update(float delta)
{
    if (!active_) return;

    for (auto& kv : field_->get_view_list())
    {
        auto object_ = kv.second;

        auto stat_info = object_->get_stat_info();

        if (check_intersection(object_->get_pos(), stat_info->size))
        {
            wprintf(L"유저가 coin 아이템 획득\n");
         
            auto session = object_->get_session();
            if (!session)
            {
                GAME::SC_NOTI_ACQUIRE_PERSIST_ITEM noti;
                noti.set_obj_id(object_->get_object_id());
                noti.set_item_id(item_id_);
                noti.set_item_type(to_integral(type_));
                noti.set_count(0);

                field_->noti_packet(opcode::SC_NOTI_ACQUIRE_PERSIST_ITEM, noti);
                return;
            }

            session->get_account()->inc_coin_count();
            const auto count = session->get_account()->get_coin_count();

            GAME::SC_NOTI_ACQUIRE_PERSIST_ITEM noti;
            noti.set_obj_id(object_->get_object_id());
            noti.set_item_id(item_id_);
            noti.set_item_type(to_integral(type_));
            noti.set_count(count);

            field_->noti_packet(opcode::SC_NOTI_ACQUIRE_PERSIST_ITEM, noti);

            active_ = false;

            auto self = shared_from_this();
            active_timer_->expires_from_now(reactive_time_);
            active_timer_->async_wait([this, self](const boost::system::error_code& ec) {

                if (ec)
                {
                    //if(ec == boost::system::error_code::operation_canceled
                    wprintf(L"coin_item 타이머가 문제있음\n");
                    return;
                }

                active_ = true;
                field_->noti_active_item(item_id_, to_integral(type_), pos_);
            });

            return;
        }
    }

}
