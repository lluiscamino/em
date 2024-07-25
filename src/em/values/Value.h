#pragma once

#include <string>

#include <stddef.h>

namespace em::values {
class Value {
 public:
  virtual ~Value() = default;

  virtual bool operator==(const Value& other) = 0;

  virtual bool operator!=(const Value& other) = 0;

  [[nodiscard]] virtual size_t hash() const = 0;

  [[nodiscard]] virtual std::string str() const = 0;
};
}  // namespace em::values