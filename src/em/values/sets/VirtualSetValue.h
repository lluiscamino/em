#pragma once
#include "../../ast/exprs/OperatorExpression.h"
#include "../Value.h"
#include "../functions/Function.h"
#include "Set.h"

namespace em::values::sets {
  class VirtualSetValue : public Set {
   public:
    explicit VirtualSetValue(std::unique_ptr<functions::Function> function);

    bool operator==(const Value& other) override;

    [[nodiscard]] size_t hash() const override;

    [[nodiscard]] std::unique_ptr<Value> isSubsetOf(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::unique_ptr<Value> hasElement(const std::shared_ptr<Value>& other) const override;

    [[nodiscard]] std::string str() const override;

   private:
    std::unique_ptr<functions::Function> mFunction;
  };

}  // namespace em::values::sets
