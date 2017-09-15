#ifndef __PROPERTY_MANAGER_H
#define __PROPERTY_MANAGER_H

#include <array>
#include <string>
#include <vector>
#include <memory>
#include <boost/optional.hpp>
#include "../predeclare.h"

using character_level_info = std::tuple<int, int, int, int, int, int>;
struct CharacterLevelInfo {
    int max_hp_level;
    int speed_level;
    int bullet_speed_level;
    int bullet_power_level;
    int bullet_distance_level;
    int reload_time_level;
};
using character_stat_result = boost::optional<std::tuple<int, int, int, int, int, float>>;
struct CharacterStat {
    float max_hp;
    float speed;
    float bullet_speed;
    float bullet_power;
    float bullet_distance;
    float reload_time;
};

//enum class stat_type : int { max_hp, speed, bullet_speed, bullet_power, bullet_distance, reload_time };

struct character_stat
{
    std::vector<float> max_hp_stat_container;
    std::vector<float> speed_stat_container;
    std::vector<float> bullet_speed_stat_container;
    std::vector<float> bullet_power_stat_container;
    std::vector<float> bullet_distance_stat_container;
    std::vector<float> reload_time_stat_container;
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

    void LoadCharacterStatData(const std::string& path);
    boost::optional<CharacterStat> CharacterStatByLevel(int character_type, const CharacterLevelInfo& level_info) const;
    void to_print_stat() const;

private:
    std::vector<std::shared_ptr<default_stat_info>> default_stat_infos_;
    std::vector<int> default_character_medal_info_;

    std::vector<character_stat> character_stat_;
};

#endif
