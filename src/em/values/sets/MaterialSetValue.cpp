#include "MaterialSetValue.h"

#include <algorithm>
#include <functional>
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
                         return otherSetValue.hasElement(value);
                       });
  } catch (const std::bad_cast&) {
    return false;
  }
}

const ValuesSet& MaterialSetValue::values() const { return mValues; }

void MaterialSetValue::addValue(std::shared_ptr<Value> value) {
  mValues.insert(std::move(value));
}

bool MaterialSetValue::isSubsetOf(const std::shared_ptr<Set>& other) const {
  return std::all_of(
      mValues.cbegin(), mValues.cend(),
      [&other](const auto& value) { return other->hasElement(value); });
}

bool MaterialSetValue::hasElement(const std::shared_ptr<Value>& other) const {
  return mValues.count(other);
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
