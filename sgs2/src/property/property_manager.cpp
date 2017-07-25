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

    return true;
}

std::shared_ptr<default_stat_info> property_manager::get_default_stat_info(int index) const
{
    return default_stat_infos_[index];
}
