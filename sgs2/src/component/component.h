#ifndef __COMPONENT_H
#define __COMPONENT_H

#include <concurrent_queue.h>
#include "../predeclare.h"

class object;

class component : public std::enable_shared_from_this<component>
{
public:

    explicit component(object* obj);
    virtual ~component();

    void process_task();

    void send_task(task t)
    {
        q_.push(t);
    }

    virtual void update(float delta);

    //Concurrency::concurrent_queue<task>& queue();
    Concurrency::concurrent_queue<task> q_;
    object* object_;
};

#endif
