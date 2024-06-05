#pragma once
#include "../../runtime/Interpreter.h"
#include "../Value.h"

namespace em::values::functions {

  class Function : public Value {
   public:
    [[nodiscard]] virtual ast::NodeVisitor::VisitorRetValue execute(
        runtime::Interpreter& interpreter, const std::vector<std::shared_ptr<Value>>& arguments) = 0;

    explicit operator bool() const override;

    [[nodiscard]] std::unique_ptr<Value> isSubsetOf(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::unique_ptr<Value> hasElement(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::unique_ptr<Value> negation() const override;

    [[nodiscard]] std::unique_ptr<Value> unionOp(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::unique_ptr<Value> intersection(const std::shared_ptr<Value>& other) const override;
  };

}  // namespace em::values::functions
