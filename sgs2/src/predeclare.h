#ifndef __PREDECLARE_H
#define __PREDECLARE_H
#include <boost/asio/steady_timer.hpp>
//#include "component/skill/skill_component.h"

using account_id = __int64;
using object_id  = __int64;
using field_id   = int;
//using timer_milliseconds = boost::posix_time::milliseconds;
using timer_milliseconds = std::chrono::milliseconds;
using timer_ptr = std::unique_ptr<boost::asio::steady_timer>;

using uid = __int64;
//using obj_id = __int64;

constexpr static auto update_interval = 1.0f / 60.0f;
constexpr static auto max_user_per_field = 50;

using task = std::function<void()>;

enum comp_id { move_comp = 0 , skill_comp};

using bullet_id = __int64;

template<typename E>
constexpr auto to_integral(E e) -> typename std::underlying_type<E>::type
{
    return static_cast<typename std::underlying_type<E>::type>(e);
}

/*
template <class T, class Tuple>
struct Index;

template <class T, class... Types>
struct Index<T, std::tuple<T, Types...>> {
    static const std::size_t value = 0;
};

template <class T, class U, class... Types>
struct Index<T, std::tuple<U, Types...>> {
    static const std::size_t value = 1 + Index<T, std::tuple<Types...>>::value;
};
*/

//typedef std::tuple<move_component, skill_component> comp_t;

#endif
