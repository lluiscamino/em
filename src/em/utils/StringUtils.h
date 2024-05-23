#pragma once

#include <codecvt>
#include <locale>
#include <sstream>
#include <string>

namespace em::utils::string {
  template <typename T>
  std::string joinValues(const std::vector<T>& values, const std::string& delimiter) {
    std::stringstream stream;
    for (size_t i = 0; i < values.size(); i++) {
      stream << values[i];
      if (i != values.size() - 1) {
        stream << delimiter;
      }
    }
    return stream.str();
  }

  inline std::wstring stringToWstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
  }

  inline std::string wStringToString(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
  }
}  // namespace em::utils::string