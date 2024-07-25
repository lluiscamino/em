#include "Set.h"

#include "../../utils/StringUtils.h"
#include "../LiteralValue.h"
#include "../functions/NativeFunction.h"
#include "VirtualSetValue.h"

namespace em::values::sets {
bool Set::operator!=(const Value& other) { return !(*this == other); }

std::unique_ptr<Set> Set::unionOp(const std::shared_ptr<Set>& other) const {
  using namespace utils::string;
  if (auto *thisMaterialSet = dynamic_cast<const MaterialSetValue*>(this),
      *otherMaterialSet = dynamic_cast<const MaterialSetValue*>(other.get());
      thisMaterialSet && otherMaterialSet) {
    auto result = std::make_unique<MaterialSetValue>();
    std::for_each(thisMaterialSet->values().cbegin(),
                  thisMaterialSet->values().cend(),
                  [&](const auto& value) { result->addValue(value); });
    std::for_each(otherMaterialSet->values().cbegin(),
                  otherMaterialSet->values().cend(),
                  [&](const auto& value) { result->addValue(value); });
    return result;
  }
  return std::make_unique<VirtualSetValue>(
      std::make_unique<functions::NativeFunction>(
          stringToWstring(str()) + L" ∪ " + stringToWstring(other->str()),
          [self = shared_from_this(), other](const auto& args) {
            return std::make_unique<LiteralValue<bool>>(
                self->hasElement(args[0]) || other->hasElement(args[0]));
          }));
}

std::unique_ptr<Set> Set::intersection(
    const std::shared_ptr<Set>& other) const {
  using namespace utils::string;
  if (auto *thisMaterialSet = dynamic_cast<const MaterialSetValue*>(this),
      *otherMaterialSet = dynamic_cast<const MaterialSetValue*>(other.get());
      thisMaterialSet && otherMaterialSet) {
    auto result = std::make_unique<MaterialSetValue>();
    std::for_each(thisMaterialSet->values().cbegin(),
                  thisMaterialSet->values().cend(), [&](const auto& value) {
                    if (otherMaterialSet->hasElement(value)) {
                      result->addValue(value);
                    }
                  });
    return result;
  }
  return std::make_unique<VirtualSetValue>(
      std::make_unique<functions::NativeFunction>(
          stringToWstring(str()) + L" ∩ " + stringToWstring(other->str()),
          [self = shared_from_this(), other](const auto& args) {
            return std::make_unique<LiteralValue<bool>>(
                self->hasElement(args[0]) && other->hasElement(args[0]));
          }));
}
}  // namespace em::values::sets