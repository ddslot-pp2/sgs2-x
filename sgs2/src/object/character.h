#ifndef __CHARACTER_H
#define __CHARACTER_H

#include "object.h"

#include "../component/movement/move_component.h"
#include "../component/skill/skill_component.h"

class character : public object
{
public:

   
    /*
    template <typename C, typename Fn, typename... Args>
    void push_task(std::shared_ptr<object> obj, Fn f, Args&&... args)
    {
        constexpr auto index = Index<C, character_component_t>::value;

        auto comp = std::static_pointer_cast<C>(obj->components_[index]);
        auto callback = std::bind(f, comp, std::forward<Args>(args)...);
        obj->q_.push(callback);
    }
    */

};

#endif
