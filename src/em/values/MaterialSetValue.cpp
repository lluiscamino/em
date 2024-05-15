#include <sstream>
#include <string>

#include "MaterialSetValue.h"

#include "LiteralValue.h"

namespace em::values {
  MaterialSetValue::MaterialSetValue(ValuesSet values) : mValues(std::move(values)) {}

  bool MaterialSetValue::operator==(const Value& other) {
    try {
      auto& otherSetValue = dynamic_cast<const MaterialSetValue&>(other);
      return mValues == otherSetValue.mValues;
    } catch (const std::bad_cast&) {
      return false;
    }
  }

  bool MaterialSetValue::operator!=(const Value& other) {
    return !(*this == other);
  }

  MaterialSetValue::operator bool() const {
    throw std::logic_error("MaterialSetValue::operator bool: not supported");
  }

  const ValuesSet& MaterialSetValue::values() const {
    return mValues;
  }

  void MaterialSetValue::addValue(std::shared_ptr<Value> value) {
    mValues.insert(std::move(value));
  }

  std::unique_ptr<Value> MaterialSetValue::isSubsetOf(const std::shared_ptr<Value>& other) const {
    for (const auto& value : mValues) {
      if (!(other->hasElement(value)->isTruthy())) {
        return std::make_unique<LiteralValue<bool>>(false);
      }
    }
    return std::make_unique<LiteralValue<bool>>(true);
  }

  std::unique_ptr<Value> MaterialSetValue::hasElement(const std::shared_ptr<Value>& other) const {
    return std::make_unique<LiteralValue<bool>>(mValues.count(other));
  }

  std::unique_ptr<Value> MaterialSetValue::negation() const {
    throw std::logic_error("SetValue::negation: not supported");
  }

  std::unique_ptr<Value> MaterialSetValue::unionOp(const std::shared_ptr<Value>& other) const {
    auto result = std::make_unique<MaterialSetValue>(mValues);
    if (auto* otherSetValue = dynamic_cast<MaterialSetValue*>(other.get())) {
      for (const auto& value : otherSetValue->values()) {
        result->addValue(value);
      }
    } else {
      throw std::invalid_argument(std::string("MaterialSetValue::unionOp: other value (") + other->str() +
                                  ") must be an instance of SetValue");
    }
    return result;
  }

  std::unique_ptr<Value> MaterialSetValue::intersection(const std::shared_ptr<Value>& other) const {
    auto result = std::make_unique<MaterialSetValue>();
    if (auto* otherSetValue = dynamic_cast<MaterialSetValue*>(other.get())) {
      for (const auto& value : mValues) {
        if (otherSetValue->mValues.count(value)) {
          result->addValue(value);
        }
      }
    } else {
      throw std::invalid_argument(std::string("MaterialSetValue::intersection: other value (") + other->str() +
                                  ") must be an instance of SetValue");
    }
    return result;
  }

  std::string MaterialSetValue::str() const {
    std::stringstream stream;
    auto valuesSize = mValues.size();
    stream << "{";
    std::for_each(mValues.begin(), mValues.end(), [&stream, valuesSize, idx = 0](const auto& value) mutable {
      stream << value->str();
      if (idx++ < valuesSize - 1) {
        stream << ", ";
      }
    });
    stream << "}";
    return stream.str();
  }
}  // namespace em::values