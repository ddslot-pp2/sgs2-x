#ifndef __STRING_HELPER_H
#define __STRING_HELPER_H
#include <string>

namespace core
{
    std::wstring utf8_to_wstring(const std::string& str);

    std::wstring    string_to_wstring(std::string bytes);
    std::string     wstring_to_string(std::wstring wstr);
}

#endif
