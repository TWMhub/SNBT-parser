#include "SNBT.h"

namespace depozit
{
    std::wstring stringToWstring(const std::string& str) {
        return std::wstring(str.begin(), str.end());
    }

    std::string wstringToString(const std::wstring& wstr) {
        return std::string(wstr.begin(), wstr.end());
    }
}