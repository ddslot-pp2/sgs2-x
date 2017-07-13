#include "component.h"
#include "../object/object.h"

component::component(object* obj)
{
    object_ = obj;
}

component::~component()
{

}

void component::process_task()
{
    task t;
    while (q_.try_pop(t))
    {
        t();
    }
}

void component::update(float delta)
{
    //process_task();
}

void component::destroy()
{
    q_.clear();
}

void component::reset()
{
    q_.clear();
}