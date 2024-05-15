#pragma once

#include <memory>
#include "../../Token.h"
#include "Expression.h"

namespace em::ast::exprs {

  class OperatorExpression : public Expression {
   public:
    OperatorExpression(std::unique_ptr<Expression> left, TokenType mOperator, std::unique_ptr<Expression> right);

    [[nodiscard]] const std::unique_ptr<Expression>& leftExpression() const;

    [[nodiscard]] const std::unique_ptr<Expression>& rightExpression() const;

    [[nodiscard]] TokenType operation() const;

    NodeVisitor::VisitorRetValue accept(NodeVisitor& visitor) override;

   private:
    std::unique_ptr<Expression> mLeft, mRight;
    TokenType mOperator;
  };

}  // namespace em::ast::exprs
