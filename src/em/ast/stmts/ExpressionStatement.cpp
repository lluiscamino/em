#include "ExpressionStatement.h"

namespace em::ast::stmts {

  ExpressionStatement::ExpressionStatement(std::unique_ptr<exprs::Expression> expression)
      : mExpression(std::move(expression)) {}

  const std::unique_ptr<exprs::Expression>& ExpressionStatement::expression() const {
    return mExpression;
  }

  void ExpressionStatement::accept(NodeVisitor& visitor) {
    return visitor.visit(this);
  }
}  // namespace em::ast::stmts