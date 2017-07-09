#ifndef __OBJECT_H
#define __OBJECT_H

#include <memory>
#include <map>
#include <concurrent_queue.h>
#include "../predeclare.h"
#include "../component/component.h"

class object : public std::enable_shared_from_this<object>
{

public:
    std::shared_ptr<component> get_component(comp_id type);
    void process_task();

protected:
    std::map<comp_id, std::shared_ptr<component>> components_;
};

#endif
