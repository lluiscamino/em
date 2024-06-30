#include "NativeFunction.h"

#include "../../utils/StringUtils.h"

namespace em::values::functions {
NativeFunction::NativeFunction(std::wstring identifier,
                               ImplementationFunction implementation)
    : mIdentifier(std::move(identifier)),
      mImplementation(std::move(implementation)) {}

bool NativeFunction::operator==(const Value& other) { return this == &other; }

bool NativeFunction::operator!=(const Value& other) {
  return !(*this == other);
}

size_t NativeFunction::hash() const {
  return std::hash<std::wstring>()(mIdentifier);
}

std::string NativeFunction::str() const {
  return "NativeFunction<" + utils::string::wStringToString(mIdentifier) + ">";
}

ast::NodeVisitor::VisitorRetValue NativeFunction::execute(
    runtime::Interpreter& interpreter,
    const std::vector<std::shared_ptr<Value>>& arguments) {
  return mImplementation(arguments);
}

}  // namespace em::values::functions
