#ifndef __TIMER_HELPER_H
#define __TIMER_HELPER_H

#include <chrono>

namespace core
{
    template <typename T = std::chrono::milliseconds>
    T timestamp()
    {
        return std::chrono::duration_cast<T>(std::chrono::system_clock::now().time_since_epoch());
    }

}
#endif
