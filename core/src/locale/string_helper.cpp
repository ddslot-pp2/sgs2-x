#include "string_helper.h"
#include <vector>
#ifndef __linux__
#include <windows.h>
#endif
#include <codecvt>

namespace core
{
    static thread_local std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;

    std::wstring utf8_to_wstring(const std::string& str)
    {
        return cvt.from_bytes(str);
    }

    std::string wstring_to_utf8(const std::wstring& str)
    {
        //std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
        return cvt.to_bytes(str);
    }

    std::wstring string_to_wstring(std::string bytes)
    {
        try
        {
            return cvt.from_bytes(bytes);
        }
        catch (std::range_error& e)
        {
            thread_local wchar_t buf[1024] = { 0 };
            if (bytes.length() >= sizeof(buf) - 1)
            {
                return{};
            }

            thread_local size_t converted = 0;
            mbstowcs_s(&converted, buf, bytes.c_str(), sizeof(buf));
            return buf;
        }
        catch (std::exception& e)
        {
            return{}; 
        }
    }

    std::string wstring_to_string(std::wstring wstr)
    {
        try
        {
            return cvt.to_bytes(wstr);
        }
        catch (std::exception& e)
        {
            
            return{};
        }
    }

}
