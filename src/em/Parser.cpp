#include <unordered_set>

#include "Parser.h"

#include "ast/Program.h"
#include "ast/exprs/AssignmentExpression.h"
#include "ast/exprs/FunctionCall.h"
#include "ast/exprs/FunctionDeclaration.h"
#include "ast/exprs/GroupExpression.h"
#include "ast/exprs/LiteralExpression.h"
#include "ast/exprs/MaterialSetExpression.h"
#include "ast/exprs/OperatorExpression.h"
#include "ast/exprs/VariableExpression.h"
#include "ast/exprs/VirtualSetExpression.h"
#include "ast/stmts/ExpressionStatement.h"
#include "values/LiteralValue.h"

namespace em {
  Parser::Parser(std::vector<Token> tokens) : mTokens(std::move(tokens)) {}

  std::unique_ptr<ast::Program> Parser::parse() {
    std::vector<std::unique_ptr<ast::stmts::Statement>> stmts;
    while (!check(TokenType::END_OF_FILE)) {
      stmts.emplace_back(parseStatement());
    }
    return std::make_unique<ast::Program>(std::move(stmts));
  }

  std::unique_ptr<ast::stmts::Statement> Parser::parseStatement() {
    auto expr = parseExpression();
    if (!check(TokenType::END_OF_FILE)) {
      consume(TokenType::LINE_BREAK);
    }
    return std::make_unique<ast::stmts::ExpressionStatement>(std::move(expr));
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseExpression() {
    return parseAssignment();
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseAssignment() {
    auto left = parseBelonging();
    while (match(TokenType::ASSIGN)) {
      auto right = parseExpression();
      if (auto* variableExpr = dynamic_cast<ast::exprs::VariableExpression*>(left.get())) {
        left = std::make_unique<ast::exprs::AssignmentExpression>(variableExpr->token(), std::move(right));
      } else {
        throw std::logic_error("Invalid assignment target");
      }
    }
    return left;
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseBelonging() {
    auto left = parseEquality();
    while (match({TokenType::ELEMENT_OF})) {
      left = std::make_unique<ast::exprs::OperatorExpression>(std::move(left), previous(), parseSetOperation());
    }
    return left;
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseEquality() {
    auto left = parseSetOperation();
    while (match({TokenType::EQUAL, TokenType::NOT_EQUAL})) {
      left = std::make_unique<ast::exprs::OperatorExpression>(std::move(left), previous(), parseSetOperation());
    }
    return left;
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseSetOperation() {
    auto left = parseSet();
    while (match({TokenType::UNION, TokenType::INTERSECTION, TokenType::SUBSET, TokenType::NOT_SUBSET})) {
      left = std::make_unique<ast::exprs::OperatorExpression>(std::move(left), previous(), parseSet());
    }
    return left;
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseSet() {
    if (match(TokenType::LEFT_BRACE)) {
      auto exprs = std::unordered_set<std::unique_ptr<ast::exprs::Expression>>();
      if (!check(TokenType::RIGHT_BRACE)) {
        do {
          exprs.insert(parseExpression());
          if (match(TokenType::VERTICAL_BAR)) {
            auto leftExpr = dynamic_cast<ast::exprs::VariableExpression*>((*exprs.begin()).get());
            if (exprs.size() != 1 || !leftExpr) {
              throw std::logic_error("Invalid virtual set variable");
            }
            auto rightExpr = parseExpression();
            consume(TokenType::RIGHT_BRACE);
            return std::make_unique<ast::exprs::VirtualSetExpression>(leftExpr->token(), std::move(rightExpr));
          }
        } while (match(TokenType::COMMA));
      }
      mPosition++;
      return std::make_unique<ast::exprs::MaterialSetExpression>(std::move(exprs));
    }
    return parseFunctionDeclaration();
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseFunctionDeclaration() {
    auto positionBackup = mPosition;
    if (matchSequence({TokenType::IDENTIFIER, TokenType::LEFT_PAREN})) {
      auto identifier = mTokens[mPosition - 2];
      std::vector<Token> params;
      if (!check(TokenType::RIGHT_PAREN)) {
        do {
          if (check(TokenType::IDENTIFIER)) {
            params.emplace_back(consume(TokenType::IDENTIFIER));
          } else {
            mPosition = positionBackup;
            return parseFunctionCall();
          }
        } while (match(TokenType::COMMA));
      }
      consume(TokenType::RIGHT_PAREN);
      if (check(TokenType::EQUAL)) {
        consume(TokenType::EQUAL);
      } else {
        mPosition = positionBackup;
        return parseFunctionCall();
      }
      return std::make_unique<ast::exprs::FunctionDeclaration>(identifier, params, parseExpression());
    }
    return parseFunctionCall();
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseFunctionCall() {
    auto expr = parsePrimary();
    while (true) {
      if (match(TokenType::LEFT_PAREN)) {
        expr = finishFunctionCall(std::move(expr));
      } else {
        break;
      }
    }
    return expr;
  }

  std::unique_ptr<ast::exprs::Expression> Parser::finishFunctionCall(
      std::unique_ptr<ast::exprs::Expression> expression) {
    std::vector<std::unique_ptr<ast::exprs::Expression>> args;
    if (!check(TokenType::RIGHT_PAREN)) {
      do {
        args.emplace_back(parseExpression());
      } while (match(TokenType::COMMA));
    }
    consume(TokenType::RIGHT_PAREN);
    return std::make_unique<ast::exprs::FunctionCall>(std::move(expression), std::move(args));
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parsePrimary() {
    if (match(TokenType::NUMBER)) {
      return std::make_unique<ast::exprs::LiteralExpression>(
          std::make_unique<values::LiteralValue<int>>(std::stoi(previous().text())));
    }
    if (match(TokenType::IDENTIFIER)) {
      return std::make_unique<ast::exprs::VariableExpression>(previous());
    }
    if (match(TokenType::LEFT_PAREN)) {
      auto expr = parseExpression();
      consume(TokenType::RIGHT_PAREN);
      return std::make_unique<ast::exprs::GroupExpression>(std::move(expr));
    }
    throw std::logic_error("Unrecognized syntax node");
  }

  Token Parser::previous() const {
    return mTokens[mPosition - 1];
  }

  Token Parser::consume(TokenType tokenType) {
    if (match(tokenType)) {
      return previous();
    }
    throw std::logic_error("Expected " + TokenTypeToString(tokenType));
  }

  bool Parser::match(TokenType tokenType) {
    return match({tokenType});
  }

  bool Parser::match(std::initializer_list<TokenType> tokenTypes) {
    auto res = std::any_of(tokenTypes.begin(), tokenTypes.end(), [&](auto tokenType) { return check(tokenType); });
    if (res) {
      mPosition++;
    }
    return res;
  }

  bool Parser::matchSequence(std::vector<TokenType> tokenTypes) {
    for (size_t i = 0; i < tokenTypes.size(); i++) {
      if (mTokens[mPosition + i].type() != tokenTypes[i]) {
        return false;
      }
    }
    mPosition += tokenTypes.size();
    return true;
  }

  bool Parser::check(TokenType tokenType) const {
    return mTokens[mPosition].type() == tokenType;
  }
}  // namespace em
