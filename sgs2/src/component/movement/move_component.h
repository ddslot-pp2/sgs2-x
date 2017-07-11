#ifndef __MOVE_COMPONENT_H
#define __MOVE_COMPONENT_H

#include "../component.h"

class vector3;

class move_component : public component
{
public:

    explicit move_component(object* obj);
    virtual ~move_component();

    void update(float delta) override;

    void set_pos(const vector3& pos);

    void say_hello();
    //void process_task() override;
};

#endif
