#pragma once
#include <memory>

namespace em::values {
  class Value : public std::enable_shared_from_this<Value> {
   public:
    virtual ~Value() = default;

    virtual bool operator==(const Value& other) = 0;

    virtual bool operator!=(const Value& other) = 0;

    virtual explicit operator bool() const = 0;

    [[nodiscard]] virtual size_t hash() const = 0;

    [[nodiscard]] bool isTruthy() const;

    [[nodiscard]] std::unique_ptr<Value> isEqualTo(const std::shared_ptr<Value>& other);

    [[nodiscard]] std::unique_ptr<Value> isDifferentTo(const std::shared_ptr<Value>& other);

    [[nodiscard]] virtual std::unique_ptr<Value> isSubsetOf(const std::shared_ptr<Value>& other) const = 0;

    [[nodiscard]] virtual std::unique_ptr<Value> hasElement(const std::shared_ptr<Value>& other) const = 0;

    [[nodiscard]] std::unique_ptr<Value> isElementOf(const std::shared_ptr<Value>& other);

    [[nodiscard]] std::unique_ptr<Value> isNotSubsetOf(const std::shared_ptr<Value>& other) const;

    [[nodiscard]] virtual std::unique_ptr<Value> negation() const = 0;

    [[nodiscard]] virtual std::unique_ptr<Value> unionOp(const std::shared_ptr<Value>& other) const = 0;

    [[nodiscard]] virtual std::unique_ptr<Value> intersection(const std::shared_ptr<Value>& other) const = 0;

    [[nodiscard]] virtual std::string str() const = 0;
  };
}  // namespace em::values