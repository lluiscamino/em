#include "FunctionDeclaration.h"

namespace em::ast::exprs {
FunctionDeclaration::FunctionDeclaration(Token identifier,
                                         std::vector<Token> parameters,
                                         std::shared_ptr<Expression> expression)
    : mIdentifier(std::move(identifier)),
      mParameters(std::move(parameters)),
      mExpression(std::move(expression)) {}

const Token& FunctionDeclaration::identifier() const { return mIdentifier; }

const std::vector<Token>& FunctionDeclaration::parameters() const {
  return mParameters;
}

const std::shared_ptr<Expression>& FunctionDeclaration::expression() const {
  return mExpression;
}

NodeVisitor::VisitorRetValue FunctionDeclaration::accept(NodeVisitor& visitor) {
  return visitor.visit(this);
}
}  // namespace em::ast::exprs