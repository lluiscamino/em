#include "Function.h"

namespace em::values::functions {
Function::operator bool() const {
  throw std::logic_error("Function::bool: not supported");
}

std::unique_ptr<Value> Function::isSubsetOf(
    const std::shared_ptr<Value>& other) const {
  throw std::logic_error("Function::isSubsetOf: not supported");
}

std::unique_ptr<Value> Function::hasElement(
    const std::shared_ptr<Value>& other) const {
  throw std::logic_error("Function::hasElement: not supported");
}

std::unique_ptr<Value> Function::negation() const {
  throw std::logic_error("Function::negation: not supported");
}

std::unique_ptr<Value> Function::unionOp(
    const std::shared_ptr<Value>& other) const {
  throw std::logic_error("Function::unionOp: not supported");
}

std::unique_ptr<Value> Function::intersection(
    const std::shared_ptr<Value>& other) const {
  throw std::logic_error("Function::intersection: not supported");
}
}  // namespace em::values::functions