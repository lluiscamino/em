#pragma once

#include <memory>
#include <unordered_set>
#include "Expression.h"

namespace em::ast::exprs {
  class MaterialSetExpression : public Expression {
   public:
    explicit MaterialSetExpression(std::unordered_set<std::unique_ptr<Expression>> values);

    [[nodiscard]] const std::unordered_set<std::unique_ptr<Expression>>& values() const;

    NodeVisitor::VisitorRetValue accept(NodeVisitor& visitor) override;

   private:
    std::unordered_set<std::unique_ptr<Expression>> mValues;
  };
}  // namespace em::ast::exprs

// lang
