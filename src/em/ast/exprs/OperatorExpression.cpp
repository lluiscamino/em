#include "OperatorExpression.h"

namespace em::ast::exprs {
  OperatorExpression::OperatorExpression(std::unique_ptr<Expression> left, TokenType mOperator,
                                         std::unique_ptr<Expression> right)
      : mLeft(std::move(left)), mOperator(mOperator), mRight(std::move(right)) {}

  TokenType OperatorExpression::operation() const {
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