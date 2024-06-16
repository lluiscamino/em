#pragma once
#include <filesystem>
#include <iostream>

namespace em {
  class EmLang {
   public:
    static void runProgram(const std::wstring& program, const std::shared_ptr<std::ostream>& outputStream =
                                                            std::make_unique<std::ostream>(std::cout.rdbuf()));
  };

}  // namespace em
