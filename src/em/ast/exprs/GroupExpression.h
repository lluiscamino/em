#pragma once
#include <memory>

#include "Expression.h"

namespace em::ast::exprs {

  class GroupExpression : public Expression {
   public:
    explicit GroupExpression(std::unique_ptr<Expression> m_expression);

    [[nodiscard]] const std::unique_ptr<Expression>& expression() const;

    NodeVisitor::VisitorRetValue accept(NodeVisitor& visitor) override;

   private:
    std::unique_ptr<Expression> mExpression;
  };

}  // namespace lang::exprs
