#include "MaterialSetExpression.h"

namespace em::ast::exprs {
  MaterialSetExpression::MaterialSetExpression(std::unordered_set<std::unique_ptr<Expression>> values) : mValues(std::move(values)) {}

  NodeVisitor::VisitorRetValue MaterialSetExpression::accept(NodeVisitor& visitor) {
    return visitor.visit(this);
  }

  const std::unordered_set<std::unique_ptr<Expression>>& MaterialSetExpression::values() const {
    return mValues;
  }
}  // namespace em::ast::exprs