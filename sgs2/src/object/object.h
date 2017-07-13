#ifndef __OBJECT_H
#define __OBJECT_H

#include <memory>
#include <map>
#include <concurrent_queue.h>
#include "../predeclare.h"
#include "../component/component.h"
#include "../component/movement/move_component.h"
#include "../component/skill/skill_component.h"
#include "../../../core/src/util/vector3.h"
#include <mutex>
#include "stat_info.h"

class field;

class object : public std::enable_shared_from_this<object>
{

public:
    explicit object(field_id id);
    virtual ~object();

    virtual void initialize();
    virtual void update(float delta);

    virtual void destroy();

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
    size_t get_object_id() const;

    field_id get_field_id() const { return field_id_; }

    void set_pos(const vector3& pos);
    vector3 get_pos();

    field* get_field() const { return field_; }
    auto get_stat_info() const { return stat_; }

    //void set_destroy(bool destroy) { destroy_ = destroy; }
    bool get_destroy() const { return destroy_; }

protected:
    std::map<comp_id, std::shared_ptr<component>> components_;
    field_id field_id_;
    size_t object_id_;

    field* field_;

    vector3 pos_;

    std::shared_ptr<stat_info> stat_;
    std::shared_ptr<stat_info> default_stat_;

    bool destroy_;
};

#endif
