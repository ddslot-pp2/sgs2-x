#ifndef __COMPONENT_H
#define __COMPONENT_H

#include <concurrent_queue.h>
#include "../predeclare.h"

class component : public std::enable_shared_from_this<component>
{
public:
    void process_task();
    
    Concurrency::concurrent_queue<task> q_;
};

#endif
