#pragma once
#include "../../Token.h"
#include "Function.h"

namespace em::ast::exprs {
class Expression;
}

namespace em::values::functions {
class ProgramFunction final : public Function {
 public:
  ProgramFunction(Token identifier, std::vector<Token> parameters,
                  std::shared_ptr<ast::exprs::Expression> expression);

  bool operator==(const Value& other) override;

  bool operator!=(const Value& other) override;

  [[nodiscard]] size_t hash() const override;

  [[nodiscard]] std::string str() const override;

  [[nodiscard]] ast::NodeVisitor::VisitorRetValue execute(
      runtime::Interpreter& interpreter,
      const std::vector<std::shared_ptr<Value>>& arguments) override;

 private:
  Token mIdentifier;
  std::vector<Token> mParameters;
  std::shared_ptr<ast::exprs::Expression> mExpression;
};

}  // namespace em::values::functions
