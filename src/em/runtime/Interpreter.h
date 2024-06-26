#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "../Token.h"
#include "../ast/NodeVisitor.h"
#include "../ast/Program.h"

namespace em::runtime {
  class Interpreter : public ast::NodeVisitor {
   public:
    explicit Interpreter(std::shared_ptr<std::ostream> outputStream);

    void execute(const std::unique_ptr<ast::Program>& program);

    void addVariable(const Token& token, const VisitorRetValue& value);

    void visit(ast::Program* program) override;

    void visit(ast::stmts::ExpressionStatement* stmt) override;

    VisitorRetValue visit(ast::exprs::FunctionDeclaration* expr) override;

    VisitorRetValue visit(ast::exprs::AssignmentExpression* expr) override;

    VisitorRetValue visit(ast::exprs::OperatorExpression* expr) override;

    VisitorRetValue visit(ast::exprs::MaterialSetExpression* expr) override;

    VisitorRetValue visit(ast::exprs::VirtualSetExpression* expr) override;

    VisitorRetValue visit(ast::exprs::LiteralExpression* expr) override;

    VisitorRetValue visit(ast::exprs::GroupExpression* expr) override;

    VisitorRetValue visit(ast::exprs::VariableExpression* expr) override;

    VisitorRetValue visit(ast::exprs::FunctionCall* expr) override;

   private:
    std::unordered_map<std::wstring, VisitorRetValue> mVariables;
    std::shared_ptr<std::ostream> mOutputStream;
  };
}  // namespace em::runtime
