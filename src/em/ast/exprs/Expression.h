#pragma once

#include "../Node.h"

namespace em::ast::exprs {

  class Expression : public Node {
   public:
    virtual NodeVisitor::VisitorRetValue accept(NodeVisitor& visitor) = 0;
  };

}  // namespace em::ast::exprs
