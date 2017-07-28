#ifndef __SHIELD_ITEM_H
#define __SHIELD_ITEM_H

#include "item.h"

class shield_item : public item
{
public:
    explicit shield_item(field_id id, std::chrono::milliseconds reactive_time, const vector3& pos);
    virtual ~shield_item();
    void update(float delta) override;

    void noti_acquire_item(std::shared_ptr<character> c, std::shared_ptr<stat_info> obj_stat_info) const;
};

#endif
