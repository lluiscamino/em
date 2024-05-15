#pragma once

#include <vector>
#include "Token.h"
#include "ast/exprs/Expression.h"
#include "ast/stmts/Statement.h"

namespace em {
  class Parser {
   public:
    explicit Parser(std::vector<Token> tokens);

    std::unique_ptr<ast::Program> parse();

   private:
    std::unique_ptr<ast::stmts::Statement> parseStatement();

    std::unique_ptr<ast::exprs::Expression> parseExpression();

    std::unique_ptr<ast::exprs::Expression> parseAssignment();

    std::unique_ptr<ast::exprs::Expression> parseBelonging();

    std::unique_ptr<ast::exprs::Expression> parseEquality();

    std::unique_ptr<ast::exprs::Expression> parseSetOperation();

    std::unique_ptr<ast::exprs::Expression> parseSet();

    std::unique_ptr<ast::exprs::Expression> parsePrimary();

    [[nodiscard]] Token previous() const;

    bool match(TokenType tokenType);

    bool match(std::initializer_list<TokenType> tokenTypes);

    [[nodiscard]] bool check(TokenType tokenType) const;

    unsigned int mPosition{0};
    std::vector<Token> mTokens;
  };

}  // namespace em
