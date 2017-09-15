#include "property_manager.h"
#include "../object/stat_info.h"
#include "../exception.hpp"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

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

void property_manager::LoadCharacterStatData(const std::string& path)
{
    namespace property_tree = boost::property_tree;
    property_tree::ptree pt;
    // 읽을 xml 파일을 설정합니다.(xml 파일경로, 엮을 객체)
    try
    {
        property_tree::read_xml(path, pt);
        BOOST_FOREACH(auto const& character_stat_info, pt.get_child("character_stat_info")) 
        {
            if (character_stat_info.first == "character_stat") 
            {
                character_stat stat;
                BOOST_FOREACH(auto const& max_hp_stat, character_stat_info.second.get_child("max_hp_stat"))
                {
                    if (max_hp_stat.first == "max_hp")
                    {
                        auto v = max_hp_stat.second;
                        auto max_hp = v.get_value<float>();
                        stat.max_hp_stat_container.push_back(max_hp);
                    }
                }

                BOOST_FOREACH(auto const& speed_stat, character_stat_info.second.get_child("speed_stat"))
                {
                    if (speed_stat.first == "speed")
                    {
                        auto v = speed_stat.second;
                        auto speed = v.get_value<float>();
                        stat.speed_stat_container.push_back(speed);
                    }
                }

                BOOST_FOREACH(auto const& bullet_speed_stat, character_stat_info.second.get_child("bullet_speed_stat"))
                {
                    if (bullet_speed_stat.first == "bullet_speed")
                    {
                        auto v = bullet_speed_stat.second;
                        auto bullet_speed = v.get_value<float>();
                        stat.bullet_speed_stat_container.push_back(bullet_speed);
                    }
                }

                BOOST_FOREACH(auto const& bullet_power_stat, character_stat_info.second.get_child("bullet_power_stat"))
                {
                    if (bullet_power_stat.first == "bullet_power")
                    {
                        auto v = bullet_power_stat.second;
                        auto bullet_power = v.get_value<float>();
                        stat.bullet_power_stat_container.push_back(bullet_power);
                    }
                }

                BOOST_FOREACH(auto const& bullet_distance_stat, character_stat_info.second.get_child("bullet_distance_stat"))
                {
                    if (bullet_distance_stat.first == "bullet_distance")
                    {
                        auto v = bullet_distance_stat.second;
                        auto bullet_distance = v.get_value<float>();
                        stat.bullet_distance_stat_container.push_back(bullet_distance);
                    }
                }

                BOOST_FOREACH(auto const& reload_time_stat, character_stat_info.second.get_child("reload_time_stat"))
                {
                    if (reload_time_stat.first == "reload_time")
                    {
                        auto v = reload_time_stat.second;
                        auto reload_time = v.get_value<float>();
                        stat.reload_time_stat_container.push_back(reload_time);
                    }
                }

                character_stat_.push_back(stat);
            }
        }
    }
    catch (...)
    {
        throw;
    }

}

boost::optional<CharacterStat> property_manager::CharacterStatByLevel(int type, const CharacterLevelInfo& level_info) const {
    if (character_stat_.size() - 1 > type || type < 0)  return boost::none;

    auto& character_stat = character_stat_[type];

    boost::optional<CharacterStat> stat;
    stat->max_hp = character_stat.max_hp_stat_container[level_info.max_hp_level - 1];
    stat->speed = character_stat.speed_stat_container[level_info.speed_level - 1];
    stat->bullet_speed = character_stat.bullet_speed_stat_container[level_info.bullet_speed_level - 1];
    stat->bullet_power = character_stat.bullet_power_stat_container[level_info.bullet_power_level - 1];
    stat->bullet_distance = character_stat.bullet_distance_stat_container[level_info.bullet_distance_level - 1];
    stat->reload_time = character_stat.reload_time_stat_container[level_info.reload_time_level - 1];
    return stat;
}

void property_manager::to_print_stat() const
{
    auto index = 0;
    for (const auto& cstat : character_stat_)
    {
        printf("----- CHARACTER STAT %d -----\n", index++);
        printf("----- max_hp_stat -----\n");
        for (auto i = 0; i < cstat.max_hp_stat_container.size(); ++i)
        {
            printf("%f, ", cstat.max_hp_stat_container[i]);
        }
        printf("\n");

        printf("----- speed_stat -----\n");
        for (auto i = 0; i < cstat.speed_stat_container.size(); ++i)
        {
            printf("%f, ", cstat.speed_stat_container[i]);
        }
        printf("\n");

        printf("----- bullet_speed_stat -----\n");
        for (auto i = 0; i < cstat.bullet_speed_stat_container.size(); ++i)
        {
            printf("%f, ", cstat.bullet_speed_stat_container[i]);
        }
        printf("\n");

        printf("----- bullet_power_stat -----\n");
        for (auto i = 0; i < cstat.bullet_power_stat_container.size(); ++i)
        {
            printf("%f, ", cstat.bullet_power_stat_container[i]);
        }
        printf("\n");

        printf("----- bullet_distance_stat -----\n");
        for (auto i = 0; i < cstat.bullet_distance_stat_container.size(); ++i)
        {
            printf("%f, ", cstat.bullet_distance_stat_container[i]);
        }
        printf("\n");

        printf("----- reload_time_stat -----\n");
        for (auto i = 0; i < cstat.reload_time_stat_container.size(); ++i)
        {
            printf("%f, ", cstat.reload_time_stat_container[i]);
        }
        printf("\n");
    }
}