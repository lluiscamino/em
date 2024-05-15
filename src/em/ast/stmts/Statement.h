#pragma once
#include "../Node.h"

namespace em::ast::stmts {

  class Statement : public Node {
   public:
    virtual void accept(NodeVisitor& visitor) = 0;
  };

}  // namespace em::ast::stmts
