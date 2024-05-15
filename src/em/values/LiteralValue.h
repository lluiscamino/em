#pragma once

#include <string>
#include <typeinfo>

#include "MaterialSetValue.h"
#include "Value.h"

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

    explicit operator bool() const override { return mValue; }

    [[nodiscard]] size_t hash() const override { return std::hash<T>()(mValue); }

    [[nodiscard]] std::unique_ptr<Value> isSubsetOf(const std::shared_ptr<Value>& other) const override {
      throw std::logic_error("LiteralValue::isSubsetOf: not supported");
    }

    [[nodiscard]] std::unique_ptr<Value> hasElement(const std::shared_ptr<Value>& other) const override {
      throw std::logic_error("LiteralValue::hasElement: not supported");
    }

    [[nodiscard]] std::unique_ptr<Value> unionOp(const std::shared_ptr<Value>& other) const override {
      throw std::logic_error("LiteralValue::unionOp: not supported");
    }

    [[nodiscard]] std::unique_ptr<Value> intersection(const std::shared_ptr<Value>& other) const override {
      throw std::logic_error("LiteralValue::intersection: not supported");
    }

    [[nodiscard]] std::unique_ptr<Value> negation() const override {
      return std::make_unique<LiteralValue<decltype(mValue)>>(!mValue);
    }

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
