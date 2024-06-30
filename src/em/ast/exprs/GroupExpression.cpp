#include "GroupExpression.h"

namespace em::ast::exprs {
GroupExpression::GroupExpression(std::unique_ptr<Expression> m_expression)
    : mExpression(std::move(m_expression)) {}

const std::unique_ptr<Expression>& GroupExpression::expression() const {
  return mExpression;
}

NodeVisitor::VisitorRetValue GroupExpression::accept(NodeVisitor& visitor) {
  return visitor.visit(this);
}
}  // namespace em::ast::exprs