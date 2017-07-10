#include "move_component.h"
#include "../../object/object.h"

using super = component;

move_component::move_component(object* obj) : component(obj)
{

}

move_component::~move_component()
{

}

void move_component::update(float dt)
{
    super::update(dt);

    wprintf(L"무브 컴포넌트 업데이트!\n");
}

void move_component::set_pos(const vector3& pos)
{
    object_->set_pos(pos);
}

void move_component::say_hello()
{
    wprintf(L"say hello!\n");
}
