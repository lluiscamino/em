#pragma once

#include <sstream>

#include "../Token.h"
#include "../ast/NodeVisitor.h"

namespace em::utils {
  class AstTreeDiagramGenerator : public ast::NodeVisitor {
   public:
    void generate(const std::unique_ptr<ast::Program>& program, const std::string& filePath);

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
    unsigned int createNode(const std::string& label);

    unsigned int createTokenNode(const Token& token);

    void linkNodes(const std::vector<unsigned int>& nodeIds, const std::string& label = "");

    std::stringstream mStream;
    unsigned int mLastNodeId{0};
    unsigned int mNumNodes{0};
  };
}  // namespace em::utils
