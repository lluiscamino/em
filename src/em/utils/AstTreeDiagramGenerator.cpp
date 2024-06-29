#include "AstTreeDiagramGenerator.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "../ast/Program.h"
#include "../ast/exprs/AssignmentExpression.h"
#include "../ast/exprs/FunctionCall.h"
#include "../ast/exprs/FunctionDeclaration.h"
#include "../ast/exprs/GroupExpression.h"
#include "../ast/exprs/LiteralExpression.h"
#include "../ast/exprs/MaterialSetExpression.h"
#include "../ast/exprs/OperatorExpression.h"
#include "../ast/exprs/VariableExpression.h"
#include "../ast/exprs/VirtualSetExpression.h"
#include "../ast/stmts/ExpressionStatement.h"
#include "StringUtils.h"

namespace em::utils {
  void AstTreeDiagramGenerator::generate(const std::unique_ptr<ast::Program>& program, const std::string& filePath) {
    program->accept(*this);
    std::ofstream file(filePath);
    file << mStream.rdbuf();
  }

  void AstTreeDiagramGenerator::visit(ast::Program* program) {
    mStream << "digraph G {\n";
    auto nodeId = createNode("Program");
    for (const auto& stmt : program->statements()) {
      stmt->accept(*this);
      linkNodes({nodeId, mLastNodeId});
    }
    mStream << "}";
  }

  void AstTreeDiagramGenerator::visit(ast::stmts::ExpressionStatement* stmt) {
    auto nodeId = createNode("ExpressionStatement");
    stmt->expression()->accept(*this);
    linkNodes({nodeId, mLastNodeId});
    mLastNodeId = nodeId;
  }

  ast::NodeVisitor::VisitorRetValue AstTreeDiagramGenerator::visit(ast::exprs::AssignmentExpression* expr) {
    auto assignmentNodeId = createNode("AssignmentExpression");

    auto identifierNodeId = createTokenNode(expr->identifier());
    linkNodes({assignmentNodeId, identifierNodeId}, "identifier");

    expr->expression()->accept(*this);
    linkNodes({assignmentNodeId, mLastNodeId}, "expr");

    mLastNodeId = assignmentNodeId;
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue AstTreeDiagramGenerator::visit(ast::exprs::OperatorExpression* expr) {
    auto nodeId = createNode("OperatorExpression");

    expr->leftExpression()->accept(*this);
    linkNodes({nodeId, mLastNodeId}, "leftExpr");

    auto tokenNode = createTokenNode(expr->operation());
    linkNodes({nodeId, tokenNode}, "operation");

    expr->rightExpression()->accept(*this);
    linkNodes({nodeId, mLastNodeId}, "rightExpr");

    mLastNodeId = nodeId;
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue AstTreeDiagramGenerator::visit(ast::exprs::MaterialSetExpression* expr) {
    auto nodeId = createNode("SetExpression");
    for (const auto& value : expr->values()) {
      value->accept(*this);
      linkNodes({nodeId, mLastNodeId});
    }
    mLastNodeId = nodeId;
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue AstTreeDiagramGenerator::visit(ast::exprs::VirtualSetExpression* expr) {
    auto nodeId = createNode("VirtualSetExpression");
    linkNodes({nodeId, createTokenNode(expr->parameter())}, "parameter");
    expr->expression()->accept(*this);
    linkNodes({nodeId, mLastNodeId}, "expr");
    mLastNodeId = nodeId;
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue AstTreeDiagramGenerator::visit(ast::exprs::LiteralExpression* expr) {
    mLastNodeId = createNode(expr->value()->str());
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue AstTreeDiagramGenerator::visit(ast::exprs::GroupExpression* expr) {
    auto nodeId = createNode("GroupExpression");
    expr->expression()->accept(*this);
    linkNodes({nodeId, mLastNodeId});
    mLastNodeId = nodeId;
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue AstTreeDiagramGenerator::visit(ast::exprs::VariableExpression* expr) {
    mLastNodeId = createNode("VariableExpression");
    auto tokenNodeId = createTokenNode(expr->token());
    linkNodes({mLastNodeId, tokenNodeId});
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue AstTreeDiagramGenerator::visit(ast::exprs::FunctionDeclaration* expr) {
    auto nodeId = createNode("FunctionDeclaration");

    auto identifierNodeId = createTokenNode(expr->identifier());
    linkNodes({nodeId, identifierNodeId}, "identifier");

    for (const auto& param : expr->parameters()) {
      linkNodes({nodeId, createTokenNode(param)}, "param");
    }

    expr->expression()->accept(*this);
    linkNodes({nodeId, mLastNodeId}, "expr");

    mLastNodeId = nodeId;
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue AstTreeDiagramGenerator::visit(ast::exprs::FunctionCall* expr) {
    auto nodeId = createNode("FunctionCall");
    expr->expression()->accept(*this);
    linkNodes({nodeId, mLastNodeId});
    for (const auto& value : expr->arguments()) {
      value->accept(*this);
      linkNodes({nodeId, mLastNodeId}, "arg");
    }
    mLastNodeId = nodeId;
    return nullptr;
  }

  unsigned int AstTreeDiagramGenerator::createNode(const std::string& label) {
    auto nodeId = mNumNodes++;
    mStream << '\t' << nodeId << "[label=\"" << label << "\"]\n";
    return nodeId;
  }

  unsigned int AstTreeDiagramGenerator::createTokenNode(const Token& token) {
    return createNode(TokenTypeToString(token.type()) + ": " + string::wStringToString(token.text()));
  }

  void AstTreeDiagramGenerator::linkNodes(const std::vector<unsigned int>& nodeIds, const std::string& label) {
    mStream << '\t' << string::joinValues(nodeIds, "->") << "[label=\"" << label << "\"]\n";
  }
}  // namespace em::utils