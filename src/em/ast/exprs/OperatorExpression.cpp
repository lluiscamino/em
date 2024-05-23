#include "OperatorExpression.h"

namespace em::ast::exprs {
  OperatorExpression::OperatorExpression(std::unique_ptr<Expression> left, Token mOperator,
                                         std::unique_ptr<Expression> right)
      : mLeft(std::move(left)), mOperator(std::move(mOperator)), mRight(std::move(right)) {}

  const Token& OperatorExpression::operation() const {
    return mOperator;
  }

  NodeVisitor::VisitorRetValue OperatorExpression::accept(NodeVisitor& visitor) {
    return visitor.visit(this);
  }

  const std::unique_ptr<Expression>& OperatorExpression::leftExpression() const {
    return mLeft;
  }

  const std::unique_ptr<Expression>& OperatorExpression::rightExpression() const {
    return mRight;
  }
}  // namespace em::ast::exprs