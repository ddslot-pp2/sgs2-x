#ifndef __PROPERTY_MANAGER_H
#define __PROPERTY_MANAGER_H

#include <string>
#include <vector>
#include <memory>

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

private:
    std::vector<std::shared_ptr<default_stat_info>> default_stat_infos_;
    std::vector<int> default_character_medal_info_;
};

#endif
