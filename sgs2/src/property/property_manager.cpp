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

#include <iostream>
void property_manager::load_character_stat(const std::string& path)
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
                BOOST_FOREACH(auto const& max_hp_stat, character_stat_info.second.get_child("max_hp_stat"))
                {
                    
                    if (max_hp_stat.first == "max_hp")
                    {
                        auto v = max_hp_stat.second;
                        auto max_hp = v.get_value<int>();

                        //auto value = std::atoi(v.data);
                    }
                    else
                    {
                        // attrib
                    }
                }
                
                /*
                BOOST_FOREACH(auto const& max_hp_stat_stat, character_stat_info.second.get_child("max_hp_stat"))
                {
                   
                }
                */

                /*
                Flight f;
                f.carrier = v.second.get<std::string>("carrier");
                f.number = v.second.get<unsigned>("number");
                f.date = v.second.get<Date>("date");
                f.cancelled = v.second.get("<xmlattr>.cancelled", false);
                ans.push_back(f);
                */
            }
        }
    }
    catch (...)
    {
        throw;
    }

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