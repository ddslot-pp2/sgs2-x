#ifndef __MEDAL_ITEM_H
#define __MEDAL_ITEM_H

#include "item.h"

class medal_item : public item
{
public:
    explicit medal_item(field_id id, std::chrono::milliseconds reactive_time, const vector3& pos);
    virtual ~medal_item();
    void update(float delta) override;

    void start_expire_timer();

private:
    std::atomic<bool> expired_;
    //void noti_acquire_item(object_id id, std::shared_ptr<stat_info> obj_stat_info) const;
};

#endif
