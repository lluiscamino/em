#pragma once

#include <iostream>
#include <unordered_set>
#include "Value.h"

namespace em::values {
  struct ValuePtrHash {
    constexpr std::size_t operator()(const std::shared_ptr<Value>& value) const { return value->hash(); }
  };

  struct ValuePtrEq {
    constexpr bool operator()(const std::shared_ptr<Value>& a, const std::shared_ptr<Value>& b) const {
      return *a == *b;
    }
  };

  using ValuesSet = std::unordered_set<std::shared_ptr<Value>, ValuePtrHash, ValuePtrEq>;

  class MaterialSetValue : public Value {
   public:
    MaterialSetValue() = default;

    explicit MaterialSetValue(ValuesSet values);

    bool operator==(const Value& other) override;

    bool operator!=(const Value& other) override;

    explicit operator bool() const override;

    [[nodiscard]] size_t hash() const override { return std::hash<ValuesSet::size_type>()(mValues.size()); }

    [[nodiscard]] const ValuesSet& values() const;

    void addValue(std::shared_ptr<Value> value);

    [[nodiscard]] std::unique_ptr<Value> isSubsetOf(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::unique_ptr<Value> hasElement(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::unique_ptr<Value> negation() const override;

    [[nodiscard]] std::unique_ptr<Value> unionOp(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::unique_ptr<Value> intersection(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::string str() const override;

   private:
    ValuesSet mValues{};
  };
}  // namespace em::values