#include "Program.h"

namespace em::ast {
Program::Program(std::vector<std::unique_ptr<stmts::Statement>> statements)
    : mStatements(std::move(statements)) {}

const std::vector<std::unique_ptr<stmts::Statement>>& Program::statements()
    const {
  return mStatements;
}

void Program::accept(NodeVisitor& visitor) { return visitor.visit(this); }

}  // namespace em::ast