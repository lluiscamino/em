#include "VirtualSetValue.h"

#include "../../utils/StringUtils.h"
#include "../../utils/ValueUtils.h"
#include "../LiteralValue.h"
#include "../functions/NativeFunction.h"

namespace em::values::sets {
VirtualSetValue::VirtualSetValue(std::unique_ptr<functions::Function> function)
    : mFunction(std::move(function)) {}

bool VirtualSetValue::operator==(const Value& other) {
  try {
    auto& otherSetValue = dynamic_cast<const VirtualSetValue&>(other);
    return mFunction ==
           otherSetValue.mFunction;  // TODO: Improve equality function
  } catch (const std::bad_cast&) {
    return false;
  }
}

size_t VirtualSetValue::hash() const { return mFunction->hash(); }

bool VirtualSetValue::isSubsetOf(const std::shared_ptr<Set>& other) const {
  throw std::logic_error("VirtualSetValue::isSubsetOf: not supported");
}

bool VirtualSetValue::hasElement(const std::shared_ptr<Value>& other) const {
  runtime::Interpreter interpreter(
      nullptr);  // TODO: Pass a valid output stream
  const auto& val = utils::values::requireType<LiteralValue<bool>>(
      mFunction->execute(interpreter, {other}),
      "Virtual set function must return a boolean!");
  return val->isTruthy();
}

std::string VirtualSetValue::str() const {
  return "{Virtual<" + mFunction->str() + ">}";
}
}  // namespace em::values::sets
