#include "object.h"

object::object(field_id id) : field_id_(id), field_(nullptr)
{
    
}

object::~object()
{

}

std::shared_ptr<component> object::get_component(comp_id id)
{
    return components_[id];
}

void object::initialize()
{
    components_[comp_id::move_comp] = std::make_shared<move_component>();
}

void object::update(float delta)
{
    for (auto& comp : components_)
    {
        comp.second->process_task();
    }
}

void object::set_object_id(size_t obj_id) noexcept
{
    object_id_ = obj_id;
}