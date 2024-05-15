#include "Value.h"
#include "LiteralValue.h"

namespace em::values {
  bool Value::isTruthy() const {
    return static_cast<bool>(*this);
  }

  std::unique_ptr<Value> Value::isEqualTo(const std::shared_ptr<Value>& other) {
    auto res = *this == *other;
    return std::make_unique<LiteralValue<bool>>(res);
  }

  std::unique_ptr<Value> Value::isDifferentTo(const std::shared_ptr<Value>& other) {
    auto res = *this != *other;
    return std::make_unique<LiteralValue<bool>>(res);
  }

  std::unique_ptr<Value> Value::isNotSubsetOf(const std::shared_ptr<Value>& other) const {
    return isSubsetOf(other)->negation();
  }

  std::unique_ptr<Value> Value::isElementOf(const std::shared_ptr<Value>& other) {
    if (auto* otherSetValue = dynamic_cast<MaterialSetValue*>(other.get())) {
      for (const auto& value : otherSetValue->values()) {
        if (*this == *value) {
          return std::make_unique<LiteralValue<bool>>(true);
        }
      }
      return std::make_unique<LiteralValue<bool>>(false);
    }
    throw std::invalid_argument(std::string("Value::isElementOf: other value (") + other->str() +
                                ") must be an instance of SetValue");
  }

}  // namespace em::values
