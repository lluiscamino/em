#pragma once
#include "../../Token.h"
#include "Expression.h"

namespace em::ast::exprs {

  class VirtualSetExpression : public Expression {
   public:
    VirtualSetExpression(Token parameter, std::shared_ptr<Expression> expression);

    [[nodiscard]] const Token& parameter() const;

    [[nodiscard]] const std::shared_ptr<Expression>& expression() const;

    NodeVisitor::VisitorRetValue accept(NodeVisitor& visitor) override;

   private:
    Token mParameter;
    std::shared_ptr<Expression> mExpression;
  };

}  // namespace em::ast::exprs
