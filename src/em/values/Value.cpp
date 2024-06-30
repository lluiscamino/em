#include "Value.h"

#include "LiteralValue.h"

namespace em::values {
bool Value::isTruthy() const { return static_cast<bool>(*this); }

std::unique_ptr<Value> Value::isEqualTo(const std::shared_ptr<Value>& other) {
  auto res = *this == *other;
  return std::make_unique<LiteralValue<bool>>(res);
}

std::unique_ptr<Value> Value::isDifferentTo(
    const std::shared_ptr<Value>& other) {
  auto res = *this != *other;
  return std::make_unique<LiteralValue<bool>>(res);
}

std::unique_ptr<Value> Value::isNotSubsetOf(
    const std::shared_ptr<Value>& other) const {
  return isSubsetOf(other)->negation();
}

std::unique_ptr<Value> Value::isElementOf(const std::shared_ptr<Value>& other) {
  return other->hasElement(shared_from_this());
}

}  // namespace em::values
