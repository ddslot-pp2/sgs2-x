#ifndef __HP_ITEM_H
#define __HP_ITEM_H

#include "item.h"

class hp_item : public item
{
public:
    explicit hp_item(field_id id, std::chrono::milliseconds reactive_time, const vector3& pos);
    virtual ~hp_item();
    void update(float delta) override;

    void noti_acquire_item(object_id id, std::shared_ptr<stat_info> obj_stat_info) const;
};

#endif
