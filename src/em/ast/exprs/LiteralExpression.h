#pragma once

#include "../../values/Value.h"
#include "Expression.h"

namespace em::ast::exprs {
  class LiteralExpression : public Expression {
   public:
    explicit LiteralExpression(std::shared_ptr<values::Value> value);

    [[nodiscard]] std::shared_ptr<values::Value> value() const;

    NodeVisitor::VisitorRetValue accept(NodeVisitor& visitor) override;

   private:
    std::shared_ptr<values::Value> mValue;
  };
}  // namespace em::ast::exprs
