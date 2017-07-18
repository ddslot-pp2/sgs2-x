#ifndef __ITEM_H
#define __ITEM_H

#include "../../../core/src/util/vector3.h"
#include <memory>
#include <chrono>
#include "../field/field.h"

class field;

class item : public std::enable_shared_from_this<item>
{
public:
    enum class type : int { hp = 0 };

    explicit item(field_id id, std::chrono::milliseconds reactive_time, const vector3& pos);
    virtual ~item();
    
    virtual void update(float delta);

    virtual void destroy();
    //void set_active(bool active) { active_ = active; }

    void set_item_id(item_id id) { item_id_ = id; }
    item_id get_item_id() const { return item_id_; }

    type get_type() const { return type_; }

    const vector3& get_pos() const { return pos_; }

    bool get_active() const { return active_; }

protected:
    bool check_intersection(const vector3& character_pos, const vector3& character_size) const;

    field_id field_id_;
    field* field_;

    std::atomic<bool> active_;
    std::chrono::milliseconds reactive_time_;

    vector3 pos_;

    timer_ptr active_timer_;
    //std::chrono::milliseconds inactive_timestamp_;

    vector3 size_;

    type type_;
    item_id item_id_;
};

#endif
