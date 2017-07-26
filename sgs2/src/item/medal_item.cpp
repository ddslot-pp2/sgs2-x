#include "medal_item.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/opcode.h"
#include "../packet_processor/send_helper.h"
//#include "../field/field.h"

medal_item::medal_item(field_id id, std::chrono::milliseconds reactive_time, const vector3& pos) : item(id, reactive_time, pos)
{
    wprintf(L"coin 아이템 생성\n");
    type_ = item::type::medal;
}

medal_item::~medal_item()
{

}

void medal_item::update(float delta)
{
    for (auto& kv : field_->get_view_list())
    {
        auto object_ = kv.second;

        auto stat_info = object_->get_stat_info();

        if (check_intersection(object_->get_pos(), stat_info->size))
        {
            wprintf(L"유저가 medal 아이템 획득\n");

            // 바로 보내준다
            auto session = object_->get_session();
            if (!session)
            {
                GAME::SC_NOTI_ACQUIRE_MEDAL_ITEM noti;
                noti.set_obj_id(object_->get_object_id());
                noti.set_item_id(item_id_);
                noti.set_count(0);

                field_->noti_packet(opcode::SC_NOTI_ACQUIRE_MEDAL_ITEM, noti);
                return;
            }

            session->get_account()->inc_medal_count();
            const auto count = session->get_account()->get_medal_count();

            GAME::SC_NOTI_ACQUIRE_MEDAL_ITEM noti;
            noti.set_obj_id(object_->get_object_id());
            noti.set_item_id(item_id_);
            noti.set_count(count);

            field_->noti_packet(opcode::SC_NOTI_ACQUIRE_MEDAL_ITEM, noti);

            active_ = false;
            return;
        }
    }
}
