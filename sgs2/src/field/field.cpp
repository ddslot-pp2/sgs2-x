#include "field.h"
#include "../../../network/src/io_helper.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include <iostream>

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

std::map<uid, std::shared_ptr<character>>& field::view_list()
{
    return characters_;
}

void field::enter_field(std::shared_ptr<server_session> session)
{
    if (characters_.size() > max_user_per_field)
    {

        return;
    }

    auto c = std::make_shared<character>(field_id_, session);
    c->initialize();

    auto object_id = reinterpret_cast<std::uintptr_t>(&(*c));

    auto it = characters_.find(object_id);
    if (it != characters_.end())
    {
      
        // error: 오브젝트 메모리 주소 겹침
        int d = 20;
        return;
    }

    characters_[object_id] = c;
    c->set_object_id(object_id);

    session->set_character(c);
    current_user_count_ = characters_.size();
}

void field::leave_field(object_id id)
{
    current_user_count_ = characters_.size();
    auto it = characters_.find(id);

    auto sess = it->second->session();

    if (it != characters_.end())
    {
        characters_.erase(id);
    }
}