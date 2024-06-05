#pragma once
#include "Function.h"

namespace em::values::functions {
  using ImplementationFunction = std::function<std::shared_ptr<Value>(const std::vector<std::shared_ptr<Value>>&)>;

  class NativeFunction : public Function {
   public:
    explicit NativeFunction(std::wstring identifier, ImplementationFunction implementation);

    bool operator==(const Value& other) override;

    bool operator!=(const Value& other) override;

    [[nodiscard]] size_t hash() const override;

    [[nodiscard]] std::string str() const override;

    [[nodiscard]] ast::NodeVisitor::VisitorRetValue execute(
        runtime::Interpreter& interpreter, const std::vector<std::shared_ptr<Value>>& arguments) override;

   private:
    std::wstring mIdentifier;
    ImplementationFunction mImplementation;
  };

}  // namespace em::values::functions
