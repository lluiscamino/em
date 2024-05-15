#include "SetExpression.h"

namespace em::ast::exprs {
  SetExpression::SetExpression(std::unordered_set<std::unique_ptr<Expression>> values) : mValues(std::move(values)) {}

  NodeVisitor::VisitorRetValue SetExpression::accept(NodeVisitor& visitor) {
    return visitor.visit(this);
  }

  const std::unordered_set<std::unique_ptr<Expression>>& SetExpression::values() const {
    return mValues;
  }
}  // namespace em::ast::exprs