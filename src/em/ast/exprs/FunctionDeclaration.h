#pragma once

#include <memory>
#include <vector>

#include "../../Token.h"
#include "Expression.h"

namespace em::ast::exprs {
  class FunctionDeclaration : public Expression {
   public:
    explicit FunctionDeclaration(Token identifier, std::vector<Token> parameters,
                                std::shared_ptr<Expression> expression);

    [[nodiscard]] const Token& identifier() const;

    [[nodiscard]] const std::vector<Token>& parameters() const;

    [[nodiscard]] const std::shared_ptr<Expression>& expression() const;

    NodeVisitor::VisitorRetValue accept(NodeVisitor& visitor) override;

   private:
    Token mIdentifier;
    std::vector<Token> mParameters;
    std::shared_ptr<Expression> mExpression;
  };

}  // namespace em::ast::exprs
