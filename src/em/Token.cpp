#include "Token.h"

#include "utils/StringUtils.h"

namespace em {
  Token::Token(TokenType type, std::wstring text) : mType(type), mText(std::move(text)) {}

  Token::Token(TokenType type, wchar_t text) : mType(type), mText(std::wstring{text}) {}

  TokenType Token::type() const {
    return mType;
  }

  std::wstring Token::text() const {
    return mText;
  }

  std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "(" << TokenTypeToString(token.mType) << ", '" << utils::string::wStringToString(token.mText) << "')";
    return os;
  }
}  // namespace em
