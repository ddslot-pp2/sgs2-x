#include "medal_item.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/opcode.h"
#include "../packet_processor/send_helper.h"
//#include "../field/field.h"

medal_item::medal_item(field_id id, std::chrono::milliseconds reactive_time, const vector3& pos) : item(id, reactive_time, pos), expired_(false)
{
    wprintf(L"medal 아이템 생성\n");
    type_ = item::type::medal;
}

medal_item::~medal_item()
{
    wprintf(L"medal 아이템 삭제\n");
}

void medal_item::update(float delta)
{
    if (expired_ && active_)
    {
        wprintf(L"medal_item 타이머 종료로 인해 삭제\n");
        GAME::SC_NOTI_ACQUIRE_PERSIST_ITEM noti;
        noti.set_obj_id(0);
        noti.set_item_id(item_id_);
        noti.set_item_type(to_integral(type_));
        noti.set_count(0);

        field_->noti_packet(opcode::SC_NOTI_ACQUIRE_PERSIST_ITEM, noti);
        active_ = false;
        return;
    }

    for (auto& kv : field_->get_view_list())
    {
        auto other = kv.second;

        auto stat_info = other->get_stat_info();

        if (check_intersection(other->get_pos(), stat_info->size))
        {
            wprintf(L"유저가 medal 아이템 획득\n");
            active_timer_->cancel();

            // 바로 보내준다
            auto session = other->get_session();
            if (!session)
            {
                GAME::SC_NOTI_ACQUIRE_PERSIST_ITEM noti;
                noti.set_obj_id(other->get_object_id());
                noti.set_item_id(item_id_);
                noti.set_item_type(to_integral(type_));
                noti.set_count(0);

                field_->noti_packet(opcode::SC_NOTI_ACQUIRE_PERSIST_ITEM, noti);

                active_ = false;
                return;
            }

            session->get_account()->inc_medal_count();
            const auto count = session->get_account()->get_medal_count();

            GAME::SC_NOTI_ACQUIRE_PERSIST_ITEM noti;
            noti.set_obj_id(other->get_object_id());
            noti.set_item_id(item_id_);
            noti.set_item_type(to_integral(type_));
            noti.set_count(count);

            field_->noti_packet(opcode::SC_NOTI_ACQUIRE_PERSIST_ITEM, noti);

            active_ = false;
            return;
        }
    }
}

void medal_item::start_expire_timer()
{
    auto self = shared_from_this();
    active_timer_->expires_from_now(reactive_time_);
    active_timer_->async_wait([this, self](const boost::system::error_code& ec) {

        if (ec)
        {
            //if(ec == boost::system::error_code::operation_canceled
            wprintf(L"medal_item 타이머가 문제있음\n");
            return;
        }

        wprintf(L"medal_item 타이머 종료 expired 상태 변경\n");
        expired_ = true;
    });
}
