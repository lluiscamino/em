#pragma once

#include <codecvt>
#include <locale>
#include <string>

namespace em::utils::string {
  inline std::wstring stringToWstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
  }

  inline std::string wStringToString(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
  }
}  // namespace em::utils::string