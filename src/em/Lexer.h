#pragma once

#include <vector>
#include "Token.h"

namespace em {

  class Lexer {
   public:
    explicit Lexer(std::wstring mProgram);

    std::vector<Token> scanTokens();

   private:
    Token scanNumber();

    Token scanIdentifier();

    static bool isValidForIdentifier(wchar_t character);

    std::wstring mProgram;
    unsigned int mPosition{0};
  };

}  // namespace em
