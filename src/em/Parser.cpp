#include <unordered_set>

#include "Parser.h"

#include "ast/Program.h"
#include "ast/exprs/AssignmentExpression.h"
#include "ast/exprs/GroupExpression.h"
#include "ast/exprs/LiteralExpression.h"
#include "ast/exprs/OperatorExpression.h"
#include "ast/exprs/SetExpression.h"
#include "ast/exprs/VariableExpression.h"
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
    match(TokenType::LINE_BREAK);  // TODO enforce
    return std::make_unique<ast::stmts::ExpressionStatement>(std::move(expr));
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseExpression() {
    return parseAssignment();
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseAssignment() {
    auto left = parseBelonging();
    while (match(TokenType::ASSIGN)) {
      auto right = parseAssignment();
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
      left = std::make_unique<ast::exprs::OperatorExpression>(std::move(left), previous().type(), parseSetOperation());
    }
    return left;
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseEquality() {
    auto left = parseSetOperation();
    while (match({TokenType::EQUAL, TokenType::NOT_EQUAL})) {
      left = std::make_unique<ast::exprs::OperatorExpression>(std::move(left), previous().type(), parseSetOperation());
    }
    return left;
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseSetOperation() {
    auto left = parseSet();
    while (match({TokenType::UNION, TokenType::INTERSECTION, TokenType::SUBSET, TokenType::NOT_SUBSET})) {
      left = std::make_unique<ast::exprs::OperatorExpression>(std::move(left), previous().type(), parseSet());
    }
    return left;
  }

  std::unique_ptr<ast::exprs::Expression> Parser::parseSet() {
    if (match(TokenType::LEFT_BRACE)) {
      auto exprs = std::unordered_set<std::unique_ptr<ast::exprs::Expression>>();
      while (!check(TokenType::RIGHT_BRACE)) {
        exprs.insert(parseExpression());
        match(TokenType::COMMA);  // TODO: enforce comma
      }
      mPosition++;
      return std::make_unique<ast::exprs::SetExpression>(std::move(exprs));
    }
    return parsePrimary();
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
      match(TokenType::RIGHT_PAREN);  // TODO: enforce right paren
      return std::make_unique<ast::exprs::GroupExpression>(std::move(expr));
    }
    return nullptr;
  }

  Token Parser::previous() const {
    return mTokens[mPosition - 1];
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

  bool Parser::check(TokenType tokenType) const {
    return mTokens[mPosition].type() == tokenType;
  }
}  // namespace em
