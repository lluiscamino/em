#pragma once

#include <string>
#include <typeinfo>

#include "Value.h"
#include "sets/MaterialSetValue.h"

namespace em::values {
template <class T>
class LiteralValue : public Value {
 public:
  explicit LiteralValue(T value) : mValue(value) {}

  bool operator==(const Value& other) override {
    try {
      auto& otherLiteralValue = dynamic_cast<const LiteralValue&>(other);
      return mValue == otherLiteralValue.mValue;
    } catch (const std::bad_cast&) {
      return false;
    }
  }

  bool operator!=(const Value& other) override { return !(*this == other); }

  explicit operator bool() const { return mValue; }

  [[nodiscard]] bool isTruthy() const { return static_cast<bool>(*this); }

  [[nodiscard]] size_t hash() const override { return std::hash<T>()(mValue); }

  [[nodiscard]] std::string str() const override {
    if constexpr (std::is_same_v<decltype(mValue), bool>) {
      return mValue ? "⊤" : "⊥";
    }
    return std::to_string(mValue);
  }

 private:
  T mValue;
};
}  // namespace em::values
