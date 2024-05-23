#pragma once
#include "../../runtime/Interpreter.h"
#include "../Value.h"

namespace em::values {

  class Function : public Value {
   public:
    [[nodiscard]] virtual ast::NodeVisitor::VisitorRetValue execute(runtime::Interpreter& interpreter) = 0;
  };

}  // namespace em::values
