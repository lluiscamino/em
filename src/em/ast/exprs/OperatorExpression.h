#pragma once

#include <memory>
#include "../../Token.h"
#include "Expression.h"

namespace em::ast::exprs {

  class OperatorExpression : public Expression {
   public:
    OperatorExpression(std::unique_ptr<Expression> left, Token mOperator, std::unique_ptr<Expression> right);

    [[nodiscard]] const std::unique_ptr<Expression>& leftExpression() const;

    [[nodiscard]] const std::unique_ptr<Expression>& rightExpression() const;

    [[nodiscard]] const Token& operation() const;

    NodeVisitor::VisitorRetValue accept(NodeVisitor& visitor) override;

   private:
    std::unique_ptr<Expression> mLeft, mRight;
    Token mOperator;
  };

}  // namespace em::ast::exprs
