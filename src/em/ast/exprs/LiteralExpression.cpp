#include "LiteralExpression.h"
#include <algorithm>

namespace em::ast::exprs {
  LiteralExpression::LiteralExpression(std::shared_ptr<values::Value> value) : mValue(std::move(value)) {}

  std::shared_ptr<values::Value> LiteralExpression::value() const {
    return mValue;
  }

  NodeVisitor::VisitorRetValue LiteralExpression::accept(NodeVisitor& visitor) {
    return visitor.visit(this);
  }

}  // namespace em::ast::exprs