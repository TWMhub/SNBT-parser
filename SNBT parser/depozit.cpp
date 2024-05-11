#include "SNBT.h"

namespace depozit
{
    std::wstring stringToWstring(const std::string& str)   //convert string to wstring
    {
        int length = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
        if (length == 0)
        {
            return L"";
        }
        std::wstring wstr(length, 0);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], length);
        return wstr;
    }

    std::string wstringToString(const std::wstring& wstr)   //convert wstring to string
    {
        int length = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (length == 0)
        {
            return "";
        }
        std::string str(length, 0);
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], length, nullptr, nullptr);
        return str;
    }
    type wstringToType(const std::wstring& wstr) {
        if (wstr == L"title")
            return type::title;
        else if (wstr == L"subtitle")
            return type::subtitle;
        else if (wstr == L"description")
            return type::description;
        else
            return type::unknown;
    }
}