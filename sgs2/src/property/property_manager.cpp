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
