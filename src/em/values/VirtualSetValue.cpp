#include "VirtualSetValue.h"

#include "../ast/exprs/LiteralExpression.h"
#include "LiteralValue.h"

namespace em::values {
  VirtualSetValue::VirtualSetValue(std::unique_ptr<ast::exprs::LiteralExpression> expression)
      : mExpression(std::move(expression)) {}

  bool VirtualSetValue::operator==(const Value& other) {
    return true;
  }

  bool VirtualSetValue::operator!=(const Value& other) {
    return false;
  }

  VirtualSetValue::operator bool() const {
    throw std::logic_error("VirtualSetValue::operator bool: not supported");
  }

  size_t VirtualSetValue::hash() const {
    return std::hash<std::unique_ptr<ast::exprs::LiteralExpression>>()(mExpression);
  }

  std::unique_ptr<Value> VirtualSetValue::isSubsetOf(const std::shared_ptr<Value>& other) const {
    throw std::logic_error("VirtualSetValue::isSubsetOf: TBD");
  }

  std::unique_ptr<Value> VirtualSetValue::hasElement(const std::shared_ptr<Value>& other) const {
    return std::make_unique<LiteralValue<bool>>(mExpression->value()->isTruthy());
  }

  std::unique_ptr<Value> VirtualSetValue::negation() const {
    throw std::logic_error("VirtualSetValue::negation: TBD");
  }

  std::unique_ptr<Value> VirtualSetValue::unionOp(const std::shared_ptr<Value>& other) const {
    throw std::logic_error("VirtualSetValue::unionOp: TBD");
  }

  std::unique_ptr<Value> VirtualSetValue::intersection(const std::shared_ptr<Value>& other) const {
    throw std::logic_error("VirtualSetValue::intersection: TBD");
  }

  std::string VirtualSetValue::str() const {
    return "{Virtual}";
  }
}  // namespace em::values
