#pragma once
#include "../../runtime/Interpreter.h"
#include "../Value.h"

namespace em::values::functions {

class Function : public Value {
 public:
  [[nodiscard]] virtual ast::NodeVisitor::VisitorRetValue execute(
      runtime::Interpreter& interpreter,
      const std::vector<std::shared_ptr<Value>>& arguments) = 0;
};

}  // namespace em::values::functions
