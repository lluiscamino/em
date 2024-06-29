#include "Lexer.h"

#include "utils/StringUtils.h"

namespace em {
  Lexer::Lexer(std::wstring mProgram) : mProgram(std::move(mProgram)) {}

  std::vector<Token> Lexer::scanTokens() {
    std::vector<Token> tokens;
    while (mPosition < mProgram.size()) {
      switch (auto c = mProgram[mPosition]) {
        case '{':
          tokens.emplace_back(TokenType::LEFT_BRACE, c);
          break;
        case '}':
          tokens.emplace_back(TokenType::RIGHT_BRACE, c);
          break;
        case '(':
          tokens.emplace_back(TokenType::LEFT_PAREN, c);
          break;
        case ')':
          tokens.emplace_back(TokenType::RIGHT_PAREN, c);
          break;
        case ',':
          tokens.emplace_back(TokenType::COMMA, c);
          break;
        case '|':
          tokens.emplace_back(TokenType::VERTICAL_BAR, c);
          break;
        case ':':
          if (mProgram[++mPosition] == '=') {
            tokens.emplace_back(TokenType::ASSIGN, L":=");
            break;
          }
          throw std::logic_error("Expected = after :");
        case '=':
          tokens.emplace_back(TokenType::EQUAL, c);
          break;
        case u'≠':
          tokens.emplace_back(TokenType::NOT_EQUAL, c);
          break;
        case u'∪':
          tokens.emplace_back(TokenType::UNION, c);
          break;
        case u'∩':
          tokens.emplace_back(TokenType::INTERSECTION, c);
          break;
        case u'⊆':
          tokens.emplace_back(TokenType::SUBSET, c);
          break;
        case u'⊄':
          tokens.emplace_back(TokenType::NOT_SUBSET, c);
          break;
        case u'∈':
          tokens.emplace_back(TokenType::ELEMENT_OF, c);
          break;
        case '\n':
          tokens.emplace_back(TokenType::LINE_BREAK, L"\\n");
          break;
        default:
          if (std::isdigit(c)) {
            tokens.emplace_back(scanNumber());
          } else if (isValidForIdentifier(c)) {
            tokens.emplace_back(scanIdentifier());
          } else if (!std::isspace(c)) {
            throw std::invalid_argument("Character " + utils::string::wStringToString({c}) + " is not valid");
          }
          break;
      }
      mPosition++;
    }
    tokens.emplace_back(TokenType::END_OF_FILE, L"🔚");
    return tokens;
  }

  Token Lexer::scanNumber() {
    auto start = mPosition;
    while (mPosition < mProgram.size()) {
      if (!std::isdigit(mProgram[mPosition])) {
        break;
      }
      mPosition++;
    }
    auto len = mPosition - start;
    mPosition--;
    auto substr = mProgram.substr(start, len);
    return {TokenType::NUMBER, std::wstring(substr.cbegin(), substr.cend())};
  }

  Token Lexer::scanIdentifier() {
    auto start = mPosition;
    while (mPosition < mProgram.size()) {
      if (!isValidForIdentifier(mProgram[mPosition])) {
        break;
      }
      mPosition++;
    }
    auto len = mPosition - start;
    mPosition--;
    auto substr = mProgram.substr(start, len);
    return {TokenType::IDENTIFIER, std::wstring(substr.cbegin(), substr.cend())};
  }

  bool Lexer::isValidForIdentifier(wchar_t character) {
    return std::isalnum(character) || character == u'ℝ' || character == u'∅';
  }

}  // namespace em