#include "field.h"
#include "../../../network/src/io_helper.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include <iostream>
#include "../packet_processor/packet/LOBBY.pb.h"
#include "../packet_processor/send_helper.h"
#include "../packet_processor/packet/GAME.pb.h"
#include "../item/item.h"

using namespace network;

field::field(unsigned int field_id) : field_id_(field_id), last_update_(clock())
{

}

field::~field()
{

}

void field::initialize()
{
    current_user_count_ = characters_.size();
}

void field::update(float delta)
{
    for (auto& c : characters_)
    {
        c.second->update(delta);
    }

    for (auto& item : items_)
    {
        item->update(delta);
    }
}

void field::try_update()
{
    process_task();

    auto now = clock();
    auto t = now - last_update_;
    auto delta = static_cast<float>(t) / static_cast<float>(CLOCKS_PER_SEC);
    if (update_interval <= delta)
    {
        update(delta);
        last_update_ = now;
    }
    
    update_flag_.clear();
}

void field::process_task()
{
    task t;
    while (q_.try_pop(t))
    {
        t();
    }

    /*
    for (auto& c : characters_)
    {
        c.second->process_task();
    }
    */
}

bool field::check_update_flag()
{
    if (update_flag_.test_and_set())
    {
        //wprintf(L"write in progressing -> return@@\n");
        return false;
    }

    return true;
}

std::map<uid, std::shared_ptr<character>>& field::get_view_list()
{
    return characters_;
}

void field::enter_field(std::shared_ptr<server_session> session)
{
    wprintf(L"유저 필드 들어옴\n");

    LOBBY::SC_ENTER_FIELD send;
    send.set_result(true);

    if (characters_.size() > max_user_per_field)
    {
        send.set_result(false);
        send_packet(session, opcode::SC_ENTER_FIELD, send);
        return;
    }

    auto c = std::make_shared<character>(field_id_, session);
    c->initialize();

    auto object_id = reinterpret_cast<std::uintptr_t>(&(*c));

    auto it = characters_.find(object_id);
    if (it != characters_.end())
    {
        // 오브젝트 메모리 주소겹침
        send.set_result(false);
        send_packet(session, opcode::SC_ENTER_FIELD, send);
        return;
    }

    characters_[object_id] = c;
    c->set_object_id(object_id);

    vector3 spawn_pos(11.0f, 0.0f, 0.0f);
    c->set_pos(spawn_pos);

    session->set_character(c);
    current_user_count_ = characters_.size();
    send_packet(session, opcode::SC_ENTER_FIELD, send);

    wprintf(L"유저 카운트: %lld\n", characters_.size());
}

void field::leave_field(object_id id)
{
    wprintf(L"유저 필드 나감\n");
    current_user_count_ = characters_.size();
    auto it = characters_.find(id);

    if (it == characters_.end()) return;

    auto sess = it->second->get_session();

    characters_.erase(id);

    if (sess)
    {
        sess->set_character(nullptr);
        // 정상적으로 방을 나갔다고 알려줌
        //sess->
    }

    GAME::SC_NOTI_OTHER_LEAVE_FIELD noti;
    noti.set_obj_id(id);

    for (const auto& kv : characters_)
    {
        auto other = kv.second;

        auto other_session = other->get_session();
        if (!other_session) continue;

        send_packet(other_session, opcode::SC_NOTI_OTHER_LEAVE_FIELD, noti);
    }

    wprintf(L"유저 카운트: %lld\n", characters_.size());
}

void field::respawn_character(object_id id)
{
    /*
    auto it = characters_.find(id);
    if (it == characters_.end()) return;

    it->second->respawn();
    */
}

void field::sync_field(std::shared_ptr<server_session> session) const
{
    wprintf(L"sync field called\n");
}

void field::update_character_status(object_id id) const
{
    auto it = characters_.find(id);
    if (it == characters_.end()) return;
    
    auto stat_info = it->second->get_stat_info();

    GAME::SC_NOTI_UPDATE_CHARACTER_STATUS noti;
    noti.set_obj_id(id);
    noti.set_max_hp(stat_info->max_hp);
    noti.set_hp(stat_info->hp);
    noti.set_speed(stat_info->speed);
    noti.set_reload_time(stat_info->reload_time);

    for (const auto& kv : characters_)
    {
        auto other = kv.second;

        auto other_session = other->get_session();
        if (!other_session) continue;

        send_packet(other_session, opcode::SC_NOTI_UPDATE_CHARACTER_STATUS, noti);
    }
}

void field::noti_active_item(const item_id& id, const int& type, const vector3& pos) const
{
    GAME::SC_NOTI_ACTIVE_ITEM noti;

    auto item_info = noti.add_item_infos();
    item_info->set_item_id(id);
    item_info->set_item_type(type);
    item_info->set_pos_x(pos.X);
    item_info->set_pos_y(pos.Y);
    item_info->set_pos_z(pos.Z);
  
    noti_packet(opcode::SC_NOTI_ACTIVE_ITEM, noti);
}

void field::noti_active_item(std::shared_ptr<server_session> session) const
{
    GAME::SC_NOTI_ACTIVE_ITEM noti;
    for (const auto& item : items_)
    {
        if (item->get_active())
        {
            auto item_info = noti.add_item_infos();
            item_info->set_item_id(item->get_item_id());
            item_info->set_item_type(to_integral(item->get_type()));

            const auto& pos = item->get_pos();
            item_info->set_pos_x(pos.X);
            item_info->set_pos_y(pos.Y);
            item_info->set_pos_z(pos.Z);
        }
    }
    
    send_packet(session, opcode::SC_NOTI_ACTIVE_ITEM, noti);
}
