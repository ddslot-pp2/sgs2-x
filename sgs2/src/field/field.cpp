#include "field.h"
#include "../../../network/src/io_helper.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include <iostream>
#include "../packet_processor/packet/LOBBY.pb.h"
#include "../packet_processor/send_helper.h"
#include "../packet_processor/packet/GAME.pb.h"

using namespace network;

field::field(unsigned int field_id) : field_id_(field_id)
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

    vector3 spawn_pos(5.0f, 0.0f, 0.0f);
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
        auto user = kv.second;

        auto other_session = user->get_session();
        if (!other_session) continue;

        send_packet(other_session, opcode::SC_NOTI_OTHER_LEAVE_FIELD, noti);
    }

    wprintf(L"유저 카운트: %lld\n", characters_.size());
}

void field::respawn_object(std::shared_ptr<server_session> session)
{

}

void field::destroy_object(object_id id)
{
    GAME::SC_NOTI_DESTROY_CHARACTER noti;

    for (auto kv : characters_)
    {
        auto other = kv.second;
        auto other_session = other->get_session();
        if (other_session)
        {
            send_packet(other_session, opcode::SC_NOTI_DESTROY_CHARACTER, noti);
        }
    }
}

void field::sync_field(std::shared_ptr<server_session> session) const
{
    wprintf(L"sync field called\n");
}