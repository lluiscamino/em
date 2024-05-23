#pragma once
#include "../../Token.h"
#include "Function.h"

namespace em::ast::exprs {
  class Expression;
}

namespace em::values {
  class ProgramFunction : public Function {
   public:
    ProgramFunction(Token identifier, std::shared_ptr<ast::exprs::Expression> expression);

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

    [[nodiscard]] ast::NodeVisitor::VisitorRetValue execute(runtime::Interpreter& interpreter) override;

   private:
    Token mIdentifier;
    std::shared_ptr<ast::exprs::Expression> mExpression;
  };

}  // namespace em::values
