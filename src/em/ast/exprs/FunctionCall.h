#pragma once
#include <memory>
#include <vector>

#include "Expression.h"

namespace em::ast::exprs {

  class FunctionCall : public Expression {
   public:
    FunctionCall(std::unique_ptr<Expression> expression, std::vector<std::unique_ptr<Expression>> arguments);

    [[nodiscard]] const std::unique_ptr<Expression>& expression() const;

    [[nodiscard]] const std::vector<std::unique_ptr<Expression>>& arguments() const;

    NodeVisitor::VisitorRetValue accept(NodeVisitor& visitor) override;

   private:
    std::unique_ptr<Expression> mExpression;
    std::vector<std::unique_ptr<Expression>> mArguments;
  };

}  // namespace em::ast::exprs
