#pragma once
#include "../ast/exprs/OperatorExpression.h"
#include "Value.h"

namespace em::values {
  class VirtualSetValue : public Value {
   public:
    explicit VirtualSetValue(std::unique_ptr<ast::exprs::LiteralExpression> expression);

    bool operator==(const Value& other) override;

    bool operator!=(const Value& other) override;

    explicit operator bool() const override;

    [[nodiscard]] size_t hash() const override;

    [[nodiscard]] std::unique_ptr<Value> isSubsetOf(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::unique_ptr<Value> hasElement(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::unique_ptr<Value> negation() const override;

    [[nodiscard]] std::unique_ptr<Value> unionOp(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::unique_ptr<Value> intersection(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::string str() const override;

   private:
    std::unique_ptr<ast::exprs::LiteralExpression> mExpression;  // todo: this should be a lambda
  };

}  // namespace em::values
