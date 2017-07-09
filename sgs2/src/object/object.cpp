#include "object.h"

std::shared_ptr<component> object::get_component(comp_id id)
{
    return components_[id];
}

void object::process_task()
{
    for (auto& comp : components_)
    {
        comp.second->process_task();
    }
}
