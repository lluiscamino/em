#pragma once

#include "../Token.h"
#include "../values/LiteralValue.h"
#include "../values/Value.h"

namespace em::utils::values {

const std::shared_ptr<em::values::LiteralValue<bool>>& toValue(bool val);

template <typename T>
std::shared_ptr<T> requireType(const std::shared_ptr<em::values::Value>& value,
                               const std::string& errorMessage) {
  if (auto castedPtr = std::dynamic_pointer_cast<T>(value)) {
    return castedPtr;
  }
  throw std::logic_error(errorMessage);
}

template <typename T>
std::shared_ptr<T> requireType(const std::shared_ptr<em::values::Value>& value,
                               const Token& token) {
  return requireType<T>(value, "Operation " + TokenTypeToString(token.type()) +
                                   " is not supported for operand " +
                                   value->str() + " at " +
                                   token.location().str());
}

}  // namespace em::utils::values