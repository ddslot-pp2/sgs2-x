#ifndef __STAT_INFO_H
#define __STAT_INFO_H

#include <atomic>
#include "../../../core/src/util/vector3.h"

class stat_info
{
public:
    std::atomic<int>   max_hp = 0;
    std::atomic<int>   hp      = 0;
    std::atomic<float> speed = 0.0f;
    std::atomic<float> reload_time = 0.0f;
    vector3 size;

    void copy(std::shared_ptr<stat_info> other)
    {
        max_hp      = other->max_hp.load();
        hp          = other->hp.load();
        speed       = other->speed.load();
        reload_time = other->reload_time.load();
        size        = other->size;
    }

};

#endif
