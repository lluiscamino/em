#include "ProgramFunction.h"

#include "../../ast/exprs/FunctionDeclaration.h"
#include "../../utils/StringUtils.h"

namespace em::values::functions {
  ProgramFunction::ProgramFunction(Token identifier, std::vector<Token> parameters,
                                   std::shared_ptr<ast::exprs::Expression> expression)
      : mIdentifier(std::move(identifier)), mParameters(std::move(parameters)), mExpression(std::move(expression)) {}

  bool ProgramFunction::operator==(const Value& other) {
    return this == &other;
  }

  bool ProgramFunction::operator!=(const Value& other) {
    return !(*this == other);
  }

  size_t ProgramFunction::hash() const {
    return std::hash<std::wstring>()(mIdentifier.text());
  }

  std::string ProgramFunction::str() const {
    return "ProgramFunction<" + utils::string::wStringToString(mIdentifier.text()) + ">";
  }

  ast::NodeVisitor::VisitorRetValue ProgramFunction::execute(runtime::Interpreter& interpreter,
                                                             const std::vector<std::shared_ptr<Value>>& arguments) {
    for (size_t i = 0; i < std::min(arguments.size(), mParameters.size()); i++) {  // TODO: Create variables environment
      interpreter.addVariable(mParameters[i], arguments[i]);
    }
    return mExpression->accept(interpreter);
  }
}  // namespace em::values::functions