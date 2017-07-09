#ifndef __OBJECT_H
#define __OBJECT_H

#include <memory>
#include <map>
#include <concurrent_queue.h>
#include "../predeclare.h"
#include "../component/component.h"
#include "../component/movement/move_component.h"

class field;

class object : public std::enable_shared_from_this<object>
{

public:
    explicit object(field_id id);
    virtual ~object();

    virtual void initialize();
    virtual void update(float delta);

    std::shared_ptr<component> get_component(comp_id type);
   
    template <typename C, typename Fn, typename... Args>
    void send_task(comp_id id, Fn fn, Args&&... args)
    {
        auto comp = std::static_pointer_cast<C>(components_[id]);

        if (!comp)
        {
            wprintf(L"objects는 살아 있지만 components는 삭제됬음\n");
            return;
        }

        auto f = [comp, fn, args...]
        {
            auto mf = std::mem_fn(fn);
            mf(comp, std::ref(args)...);
        };

        comp->send_task(f);
    }

    void set_object_id(size_t obj_id) noexcept;

protected:
    std::map<comp_id, std::shared_ptr<component>> components_;
    field_id field_id_;
    size_t object_id_;

    field* field_;
};

#endif
