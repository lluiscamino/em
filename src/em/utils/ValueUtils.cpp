#include "ValueUtils.h"

namespace em::utils::values {
namespace {
const auto TRUE = std::make_shared<em::values::LiteralValue<bool>>(true);
const auto FALSE = std::make_shared<em::values::LiteralValue<bool>>(false);
}  // namespace

const std::shared_ptr<em::values::LiteralValue<bool>>& toValue(bool val) {
  return val ? TRUE : FALSE;
}
}  // namespace em::utils::values
