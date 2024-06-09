#pragma once
#include "../Value.h"

namespace em::values::sets {

  class Set : public Value {
   public:
    bool operator!=(const Value& other) override;

    explicit operator bool() const override;

    [[nodiscard]] std::unique_ptr<Value> negation() const override;

    [[nodiscard]] std::unique_ptr<Value> unionOp(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::unique_ptr<Value> intersection(const std::shared_ptr<Value>& other) const override;
  };

}  // namespace em::values::sets
