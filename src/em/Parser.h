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

    std::unique_ptr<ast::exprs::Expression> parseFunctionDeclaration();

    std::unique_ptr<ast::exprs::Expression> parseAssignment();

    std::unique_ptr<ast::exprs::Expression> parseBelonging();

    std::unique_ptr<ast::exprs::Expression> parseEquality();

    std::unique_ptr<ast::exprs::Expression> parseSetOperation();

    std::unique_ptr<ast::exprs::Expression> parseSet();

    std::unique_ptr<ast::exprs::Expression> parsePrimary();

    [[nodiscard]] Token previous() const;

    Token consume(TokenType tokenType);

    [[nodiscard]] bool match(TokenType tokenType);

    [[nodiscard]] bool match(std::initializer_list<TokenType> tokenTypes);

    [[nodiscard]] bool matchSequence(std::vector<TokenType> tokenTypes);

    [[nodiscard]] bool check(TokenType tokenType) const;

    unsigned int mPosition{0};
    std::vector<Token> mTokens;
  };

}  // namespace em
