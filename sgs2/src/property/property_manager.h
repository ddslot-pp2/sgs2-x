#ifndef __PROPERTY_MANAGER_H
#define __PROPERTY_MANAGER_H

#include <array>
#include <string>
#include <vector>
#include <memory>
#include <boost/optional.hpp>
#include "../predeclare.h"

using character_level_info = std::tuple<int, int, int, int, int, int>;
using character_stat_result = boost::optional<std::tuple<int, int, int, int, int, float>>;

//enum class stat_type : int { max_hp, speed, bullet_speed, bullet_power, bullet_distance, reload_time };

struct character_stat
{
    std::array<int,   max_level> max_hp_stat;
    std::array<int,   max_level> speed_stat;
    std::array<int,   max_level> bullet_speed_stat;
    std::array<int,   max_level> bullet_power_stat;
    std::array<int,   max_level> bullet_distance_stat;       
    std::array<float, max_level> reload_time_stat;
};

struct default_stat_info
{
    default_stat_info(int _max_hp, float _speed, float _bullet_speed, float _bullet_power, float _bullet_distance, float _reload_time) :
    max_hp(_max_hp), speed(_speed), bullet_speed(_bullet_speed), bullet_power(_bullet_power), bullet_distance(_bullet_distance), reload_time(_reload_time) {}

    const int   max_hp;
    const float speed;
    const float bullet_speed;
    const float bullet_power;
    const float bullet_distance;
    const float reload_time;
};

class property_manager
{
public:
    static property_manager& instance() {
        static property_manager instance;
        return instance;
    }

    explicit property_manager() = default;
    property_manager(const property_manager& other) = delete;
    property_manager& operator=(const property_manager& other) = delete;

    bool read_xml(const std::wstring& path);

    std::shared_ptr<default_stat_info> get_default_stat_info(int index) const;
    int get_default_character_medal_info(int index) const;

    bool load_character_stat(const std::string& path);
    character_stat_result get_stat(int character_type, character_level_info level_info) const;

private:
    std::vector<std::shared_ptr<default_stat_info>> default_stat_infos_;
    std::vector<int> default_character_medal_info_;

    std::vector<character_stat> character_stat_;
};

#endif
