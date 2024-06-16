#pragma once
#include <codecvt>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace em::utils::file {
  inline std::wstring getFileContents(const std::filesystem::path& path) {
    if (!std::filesystem::is_regular_file(path)) {
      throw std::invalid_argument("File " + path.string() + " does not exist or is not a file!");
    }
    std::wifstream wif(path.string());
    wif.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    std::wstringstream wss;
    wss << wif.rdbuf();
    return wss.str();
  }

  inline std::vector<std::filesystem::path> getDirectories(const std::filesystem::path& path) {
    std::vector<std::filesystem::path> directories;
    for (auto& entry : std::filesystem::directory_iterator(path)) {
      if (entry.is_directory()) {
        directories.push_back(entry.path());
      }
    }
    return directories;
  }

  inline std::vector<std::filesystem::path> getEntries(const std::filesystem::path& path) {
    std::vector<std::filesystem::path> entries;
    for (auto& entry : std::filesystem::directory_iterator(path)) {
      entries.push_back(entry.path());
    }
    return entries;
  }
}  // namespace em::utils::file
