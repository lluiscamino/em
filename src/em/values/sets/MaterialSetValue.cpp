#include "MaterialSetValue.h"

#include <sstream>
#include <string>

#include "../../utils/StringUtils.h"
#include "../LiteralValue.h"
#include "VirtualSetValue.h"

namespace em::values::sets {

MaterialSetValue::MaterialSetValue(ValuesSet values)
    : mValues(std::move(values)) {}

bool MaterialSetValue::operator==(const Value& other) {
  try {
    auto& otherSetValue = dynamic_cast<const MaterialSetValue&>(other);
    return mValues.size() == otherSetValue.mValues.size() &&
           std::all_of(mValues.cbegin(), mValues.cend(),
                       [&otherSetValue](const auto& value) {
                         return otherSetValue.hasElement(value)->isTruthy();
                       });
  } catch (const std::bad_cast&) {
    return false;
  }
}

const ValuesSet& MaterialSetValue::values() const { return mValues; }

void MaterialSetValue::addValue(std::shared_ptr<Value> value) {
  mValues.insert(std::move(value));
}

std::unique_ptr<Value> MaterialSetValue::isSubsetOf(
    const std::shared_ptr<Value>& other) const {
  for (const auto& value : mValues) {
    if (!other->hasElement(value)->isTruthy()) {
      return std::make_unique<LiteralValue<bool>>(false);
    }
  }
  return std::make_unique<LiteralValue<bool>>(true);
}

std::unique_ptr<Value> MaterialSetValue::hasElement(
    const std::shared_ptr<Value>& other) const {
  return std::make_unique<LiteralValue<bool>>(mValues.count(other));
}

std::string MaterialSetValue::str() const {
  std::vector<std::string> valueStrs;
  valueStrs.reserve(mValues.size());
  std::transform(mValues.cbegin(), mValues.cend(),
                 std::back_inserter(valueStrs),
                 [](const auto& value) { return value->str(); });
  std::sort(valueStrs.begin(), valueStrs.end());
  return "{" + utils::string::joinValues(valueStrs, ", ") + "}";
}
}  // namespace em::values::sets