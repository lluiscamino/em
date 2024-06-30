#include "AssignmentExpression.h"

namespace em::ast::exprs {
AssignmentExpression::AssignmentExpression(
    Token identifier, std::unique_ptr<Expression> expression)
    : mIdentifier(std::move(identifier)), mExpression(std::move(expression)) {}

const Token& AssignmentExpression::identifier() const { return mIdentifier; }

const std::unique_ptr<Expression>& AssignmentExpression::expression() const {
  return mExpression;
}

NodeVisitor::VisitorRetValue AssignmentExpression::accept(
    NodeVisitor& visitor) {
  return visitor.visit(this);
}

}  // namespace em::ast::exprs