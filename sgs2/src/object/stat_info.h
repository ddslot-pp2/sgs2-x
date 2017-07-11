#ifndef __STAT_INFO_H
#define __STAT_INFO_H

#include <atomic>
#include "../../../core/src/util/vector3.h"

struct stat_info
{
    std::atomic<float> speed = 0.0f;
    std::atomic<int>   hp      = 0;
    
    vector3 size;
};

#endif
