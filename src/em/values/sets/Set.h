#pragma once

#include <memory>

#include "../Value.h"

namespace em::values::sets {

class Set : public Value, public std::enable_shared_from_this<Set> {
 public:
  bool operator!=(const Value& other) override;

  [[nodiscard]] virtual bool isSubsetOf(
      const std::shared_ptr<Set>& other) const = 0;

  [[nodiscard]] virtual bool hasElement(
      const std::shared_ptr<Value>& other) const = 0;

  [[nodiscard]] std::unique_ptr<Set> unionOp(
      const std::shared_ptr<Set>& other) const;

  [[nodiscard]] std::unique_ptr<Set> intersection(
      const std::shared_ptr<Set>& other) const;
};

}  // namespace em::values::sets
