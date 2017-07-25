#include "coin_item.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/opcode.h"
#include "../packet_processor/send_helper.h"

coin_item::coin_item(field_id id, std::chrono::milliseconds reactive_time, const vector3& pos) : item(id, reactive_time, pos)
{
    wprintf(L"coin ������ ����\n");
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
            wprintf(L"������ coin ������ ȹ��\n");

         
            // ���� ������ ȿ�� ����� ������ ������Ʈ
            //field_->send_task(&field::update_character_status, kv.first);
            //noti_acquire_item(kv.first, stat_info);

            active_ = false;

            auto self = shared_from_this();
            active_timer_->expires_from_now(reactive_time_);
            active_timer_->async_wait([this, self](const boost::system::error_code& ec) {

                if (ec)
                {
                    //if(ec == boost::system::error_code::operation_canceled
                    wprintf(L"hp_item Ÿ�̸Ӱ� ��������\n");
                    return;
                }

                active_ = true;
                field_->noti_active_item(item_id_, to_integral(type_), pos_);
            });

            return;
        }
    }

}
