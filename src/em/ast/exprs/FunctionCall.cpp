#include "FunctionCall.h"

namespace em::ast::exprs {
FunctionCall::FunctionCall(std::unique_ptr<Expression> expression,
                           std::vector<std::unique_ptr<Expression>> arguments)
    : mExpression(std::move(expression)), mArguments(std::move(arguments)) {}

const std::unique_ptr<Expression>& FunctionCall::expression() const {
  return mExpression;
}

const std::vector<std::unique_ptr<Expression>>& FunctionCall::arguments()
    const {
  return mArguments;
}

NodeVisitor::VisitorRetValue FunctionCall::accept(NodeVisitor& visitor) {
  return visitor.visit(this);
}

}  // namespace em::ast::exprs