#include "ProgramFunction.h"

#include "../../ast/exprs/FunctionDeclaration.h"
#include "../../utils/StringUtils.h"

namespace em::values {
  ProgramFunction::ProgramFunction(Token identifier, std::shared_ptr<ast::exprs::Expression> expression)
      : mIdentifier(std::move(identifier)), mExpression(std::move(expression)) {}

  bool ProgramFunction::operator==(const Value& other) {
    return this == &other;
  }

  bool ProgramFunction::operator!=(const Value& other) {
    return !(*this == other);
  }

  ProgramFunction::operator bool() const {
    return false;
  }

  size_t ProgramFunction::hash() const {
    return std::hash<std::wstring>()(mIdentifier.text());
  }

  std::unique_ptr<Value> ProgramFunction::isSubsetOf(const std::shared_ptr<Value>& other) const {
    throw std::logic_error("ProgramFunction::isSubsetOf: not supported");
  }

  std::unique_ptr<Value> ProgramFunction::hasElement(const std::shared_ptr<Value>& other) const {
    throw std::logic_error("ProgramFunction::hasElement: not supported");
  }

  std::unique_ptr<Value> ProgramFunction::negation() const {
    throw std::logic_error("ProgramFunction::negation: not supported");
  }

  std::unique_ptr<Value> ProgramFunction::unionOp(const std::shared_ptr<Value>& other) const {
    throw std::logic_error("ProgramFunction::unionOp: not supported");
  }

  std::unique_ptr<Value> ProgramFunction::intersection(const std::shared_ptr<Value>& other) const {
    throw std::logic_error("ProgramFunction::intersection: not supported");
  }

  std::string ProgramFunction::str() const {
    return "ProgramFunction<" + utils::string::wStringToString(mIdentifier.text()) + ">";
  }

  ast::NodeVisitor::VisitorRetValue ProgramFunction::execute(runtime::Interpreter& interpreter) {
    return mExpression->accept(interpreter);
  }
}  // namespace em::values