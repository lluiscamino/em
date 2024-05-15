#pragma once
#include "../../Token.h"
#include "Expression.h"

namespace em::ast::exprs {

  class VariableExpression : public Expression {
   public:
    explicit VariableExpression(Token token);

    [[nodiscard]] const Token& token() const;

    NodeVisitor::VisitorRetValue accept(NodeVisitor& visitor) override;

   private:
    Token mToken;
  };

}  // namespace em::exprs
