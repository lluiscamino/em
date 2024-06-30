#include "VariableExpression.h"

namespace em::ast::exprs {
VariableExpression::VariableExpression(Token token)
    : mToken(std::move(token)) {}

const Token& VariableExpression::token() const { return mToken; }

NodeVisitor::VisitorRetValue VariableExpression::accept(NodeVisitor& visitor) {
  return visitor.visit(this);
}
}  // namespace em::ast::exprs