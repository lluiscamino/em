#include "VirtualSetExpression.h"

namespace em::ast::exprs {
  VirtualSetExpression::VirtualSetExpression(Token parameter, std::shared_ptr<Expression> expression)
      : mParameter(std::move(parameter)), mExpression(std::move(expression)) {}

  NodeVisitor::VisitorRetValue VirtualSetExpression::accept(NodeVisitor& visitor) {
    return visitor.visit(this);
  }

  const Token& VirtualSetExpression::parameter() const {
    return mParameter;
  }

  const std::shared_ptr<Expression>& VirtualSetExpression::expression() const {
    return mExpression;
  }

}  // namespace em::ast::exprs