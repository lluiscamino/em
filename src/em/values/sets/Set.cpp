#include "Set.h"

#include "../../utils/StringUtils.h"
#include "../LiteralValue.h"
#include "../functions/NativeFunction.h"
#include "VirtualSetValue.h"

namespace em::values::sets {
  bool Set::operator!=(const Value& other) {
    return !(*this == other);
  }

  Set::operator bool() const {
    throw std::logic_error("Set::operator bool: not supported");
  }

  std::unique_ptr<Value> Set::negation() const {
    throw std::logic_error("Set::negation: not supported");
  }

  std::unique_ptr<Value> Set::unionOp(const std::shared_ptr<Value>& other) const {
    using namespace utils::string;
    return std::make_unique<VirtualSetValue>(std::make_unique<functions::NativeFunction>(
        stringToWstring(str()) + L" ∪ " + stringToWstring(other->str()),
        [self = shared_from_this(), other](const auto& args) {
          return std::make_unique<LiteralValue<bool>>(self->hasElement(args[0])->isTruthy() ||
                                                      other->hasElement(args[0])->isTruthy());
        }));
  }

  std::unique_ptr<Value> Set::intersection(const std::shared_ptr<Value>& other) const {
    using namespace utils::string;
    return std::make_unique<VirtualSetValue>(std::make_unique<functions::NativeFunction>(
        stringToWstring(str()) + L" ∪ " + stringToWstring(other->str()),
        [self = shared_from_this(), other](const auto& args) {
          return std::make_unique<LiteralValue<bool>>(self->hasElement(args[0])->isTruthy() &&
                                                      other->hasElement(args[0])->isTruthy());
        }));
  }
}  // namespace em::values::sets