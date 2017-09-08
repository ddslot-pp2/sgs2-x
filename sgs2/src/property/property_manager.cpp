#include "property_manager.h"
#include "../object/stat_info.h"

bool property_manager::read_xml(const std::wstring& path)
{
    // 추후 xml에서 읽어서 기본값을 맞춤
    auto stat0 = std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f);
    default_stat_infos_.emplace_back(stat0);

    auto stat1 = std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f);
    default_stat_infos_.emplace_back(stat1);

    auto stat2 = std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f);
    default_stat_infos_.emplace_back(stat2);

    auto stat3 = std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f);
    default_stat_infos_.emplace_back(stat3);

    auto stat4 = std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f);
    default_stat_infos_.emplace_back(stat4);

    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));
    default_stat_infos_.emplace_back(std::make_shared<default_stat_info>(100, 10.0f, 20.0f, 10, 25.0f, 1000.0f));


    default_character_medal_info_.push_back(1000);
    default_character_medal_info_.push_back(2000);
    default_character_medal_info_.push_back(3000);
    default_character_medal_info_.push_back(4000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);
    default_character_medal_info_.push_back(5000);

    return true;
}

std::shared_ptr<default_stat_info> property_manager::get_default_stat_info(int index) const
{
    if (index < 0 || index - 1 > default_stat_infos_.size()) return nullptr;
    
    return default_stat_infos_[index];
}

int property_manager::get_default_character_medal_info(int index) const
{
    if (index < 0 || index > default_character_medal_info_.size()) return -1;

    return default_character_medal_info_[index];
}

bool property_manager::load_character_stat(const std::string& path)
{
    return true;
}

character_stat_result property_manager::get_stat(int character_type, character_level_info level_info_tup) const
{
    if (character_stat_.size() - 1 > character_type || character_type < 0)  return boost::none;

    // out of range 체크
    auto max_hp_level          = std::get<to_constexpr_index(buff_type::max_hp)>(level_info_tup);
    auto speed_level           = std::get<to_constexpr_index(buff_type::character_speed)>(level_info_tup);
    auto bullet_speed_level    = std::get<to_constexpr_index(buff_type::bullet_speed)>(level_info_tup);
    auto bullet_power_level    = std::get<to_constexpr_index(buff_type::bullet_power)>(level_info_tup);
    auto bullet_distance_level = std::get<to_constexpr_index(buff_type::bullet_distance)>(level_info_tup);
    auto reload_time_level     = std::get<to_constexpr_index(buff_type::reload_time)>(level_info_tup);

    auto& character_stat = character_stat_[character_type];
    return std::make_tuple(
        character_stat.max_hp_stat[max_hp_level],
        character_stat.speed_stat[speed_level],
        character_stat.bullet_speed_stat[bullet_speed_level],
        character_stat.bullet_power_stat[bullet_power_level],
        character_stat.bullet_distance_stat[bullet_distance_level],
        character_stat.reload_time_stat[reload_time_level]);
}