#pragma once

#include <sstream>
#include "../ast/NodeVisitor.h"
#include "../ast/Program.h"

namespace em::utils {
  class PrintVisitor
      : public ast::NodeVisitor {  // TODO: Figure out a better name that does not include the word "Visitor"
   public:
    std::string print(const std::unique_ptr<ast::Program>& program);

    void visit(ast::Program* program) override;

    void visit(ast::stmts::ExpressionStatement* stmt) override;

    VisitorRetValue visit(ast::exprs::AssignmentExpression* expr) override;

    VisitorRetValue visit(ast::exprs::OperatorExpression* expr) override;

    VisitorRetValue visit(ast::exprs::SetExpression* expr) override;

    VisitorRetValue visit(ast::exprs::LiteralExpression* expr) override;

    VisitorRetValue visit(ast::exprs::GroupExpression* expr) override;

    VisitorRetValue visit(ast::exprs::VariableExpression* expr) override;

   private:
    std::stringstream mStream;
  };
}  // namespace em::utils
