#ifndef __STAT_INFO_H
#define __STAT_INFO_H

#include <atomic>
#include "../../../core/src/util/vector3.h"

enum class buff_type : int
{
    max_hp, character_speed, bullet_speed, bullet_power, bullet_distance, reload_time
};

class stat_info
{
public:
    std::atomic<int>   max_hp       = 0;
    std::atomic<int>   hp           = 0;
    std::atomic<float> speed        = 0.0f;
    std::atomic<float> bullet_speed = 0.0f;
    std::atomic<float> bullet_power = 0.0f;
    std::atomic<float> bullet_distance = 0.0f;
    std::atomic<float> reload_time  = 1000.0f;
    vector3 size;

    std::atomic<float> exp = 0.0f;
    std::atomic<int>   score = 0;

    std::atomic<int> enhance_buff_count = 10;

    void copy(std::shared_ptr<stat_info> other)
    {
        max_hp      = other->max_hp.load();
        hp          = other->hp.load();
        speed       = other->speed.load();
        bullet_speed = other->bullet_speed.load();
        bullet_power = other->bullet_power.load();
        bullet_distance = other->bullet_distance.load();
        reload_time = other->reload_time.load();
        size        = other->size;

        exp = other->exp.load();
        score = other->score.load();
    }

};

#endif
