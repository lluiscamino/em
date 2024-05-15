#pragma once

#include <vector>

#include "Node.h"
#include "stmts/Statement.h"

namespace em::ast {

  class Program : public Node {
   public:
    explicit Program(std::vector<std::unique_ptr<stmts::Statement>> statements);

    [[nodiscard]] const std::vector<std::unique_ptr<stmts::Statement>>& statements() const;

    void accept(NodeVisitor& visitor);

   private:
    std::vector<std::unique_ptr<stmts::Statement>> mStatements;
  };

}  // namespace em::ast
