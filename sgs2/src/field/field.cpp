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

}

void field::try_update()
{
    process_task();

    auto now = clock();
    auto t = now - last_update_;
    auto delta = static_cast<double>(t) / static_cast<float>(CLOCKS_PER_SEC);
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

    for (auto& c : characters_)
    {
        c.second->process_task();
    }
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