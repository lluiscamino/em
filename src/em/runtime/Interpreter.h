#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "../ast/NodeVisitor.h"
#include "../ast/Program.h"

namespace em::runtime {
  class Interpreter : public ast::NodeVisitor {
   public:
    Interpreter();

    void execute(const std::unique_ptr<ast::Program>& program);

    void visit(ast::Program* program) override;

    void visit(ast::stmts::ExpressionStatement* stmt) override;

    VisitorRetValue visit(ast::exprs::AssignmentExpression* expr) override;

    VisitorRetValue visit(ast::exprs::OperatorExpression* expr) override;

    VisitorRetValue visit(ast::exprs::SetExpression* expr) override;

    VisitorRetValue visit(ast::exprs::LiteralExpression* expr) override;

    VisitorRetValue visit(ast::exprs::GroupExpression* expr) override;

    VisitorRetValue visit(ast::exprs::VariableExpression* expr) override;

   private:
    std::unordered_map<std::wstring, VisitorRetValue> mVariables;
  };
}  // namespace em::runtime