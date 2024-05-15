#pragma once

#include "../../Token.h"
#include "Expression.h"

namespace em::ast::exprs {
  class AssignmentExpression : public Expression {
   public:
    AssignmentExpression(Token identifier, std::unique_ptr<Expression> expression);

    [[nodiscard]] const Token& identifier() const;

    [[nodiscard]] const std::unique_ptr<Expression>& expression() const;

    NodeVisitor::VisitorRetValue accept(NodeVisitor& visitor) override;

   private:
    Token mIdentifier;
    std::unique_ptr<Expression> mExpression;
  };

}  // namespace em::ast::exprs
