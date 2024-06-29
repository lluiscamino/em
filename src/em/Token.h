#pragma once

#include <ostream>
#include <string>

namespace em {

  enum class TokenType {
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_PAREN,
    RIGHT_PAREN,
    COMMA,
    VERTICAL_BAR,

    ASSIGN,

    EQUAL,
    NOT_EQUAL,
    UNION,
    INTERSECTION,
    SUBSET,
    NOT_SUBSET,
    ELEMENT_OF,

    NUMBER,
    IDENTIFIER,

    LINE_BREAK,
    END_OF_FILE
  };

  inline std::string TokenTypeToString(TokenType tokenType) {
    switch (tokenType) {
      case TokenType::LEFT_BRACE:
        return "LEFT_BRACKET";
      case TokenType::RIGHT_BRACE:
        return "RIGHT_BRACKET";
      case TokenType::LEFT_PAREN:
        return "LEFT_PAREN";
      case TokenType::RIGHT_PAREN:
        return "RIGHT_PAREN";
      case TokenType::COMMA:
        return "COMMA";
      case TokenType::VERTICAL_BAR:
        return "VERTICAL_BAR";
      case TokenType::ASSIGN:
        return "ASSIGN";
      case TokenType::NUMBER:
        return "NUMBER";
      case TokenType::EQUAL:
        return "EQUAL";
      case TokenType::NOT_EQUAL:
        return "NOT_EQUAL";
      case TokenType::UNION:
        return "UNION";
      case TokenType::INTERSECTION:
        return "INTERSECTION";
      case TokenType::SUBSET:
        return "SUBSET";
      case TokenType::NOT_SUBSET:
        return "NOT_SUBSET";
      case TokenType::ELEMENT_OF:
        return "ELEMENT_OF";
      case TokenType::IDENTIFIER:
        return "IDENTIFIER";
      case TokenType::LINE_BREAK:
        return "LINE_BREAK";
      case TokenType::END_OF_FILE:
        return "END_OF_FILE";
      default:
        assert(false);
    }
  }

  class Token {
   public:
    Token(TokenType type, std::wstring text);

    Token(TokenType type, wchar_t text);

    [[nodiscard]] TokenType type() const;

    [[nodiscard]] std::wstring text() const;

    friend std::ostream& operator<<(std::ostream& os, const Token& token);

   private:
    TokenType mType;
    std::wstring mText;
  };

}  // namespace em
