#include "medal_item.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/opcode.h"
#include "../packet_processor/send_helper.h"

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

            active_ = false;
            return;
        }
    }
}
