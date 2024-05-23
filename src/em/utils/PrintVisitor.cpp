#include "PrintVisitor.h"

#include "../ast/Program.h"
#include "../ast/exprs/AssignmentExpression.h"
#include "../ast/exprs/FunctionDeclaration.h"
#include "../ast/exprs/GroupExpression.h"
#include "../ast/exprs/LiteralExpression.h"
#include "../ast/exprs/OperatorExpression.h"
#include "../ast/exprs/SetExpression.h"
#include "../ast/exprs/VariableExpression.h"
#include "../ast/stmts/ExpressionStatement.h"
#include "StringUtils.h"

namespace em::utils {
  std::string PrintVisitor::print(const std::unique_ptr<ast::Program>& program) {
    program->accept(*this);
    return mStream.str();
  }

  void PrintVisitor::visit(ast::Program* program) {
    for (const auto& stmt : program->statements()) {
      stmt->accept(*this);
    }
  }

  void PrintVisitor::visit(ast::stmts::ExpressionStatement* stmt) {
    stmt->expression()->accept(*this);
    mStream << '\n';
  }

  ast::NodeVisitor::VisitorRetValue PrintVisitor::visit(ast::exprs::FunctionDeclaration* expr) {
    mStream << string::wStringToString(expr->identifier().text()) << "(";
    std::vector<std::string> paramNames;
    std::transform(expr->parameters().cbegin(), expr->parameters().cend(), std::back_inserter(paramNames),
                   [](const auto& param) { return string::wStringToString(param.text()); });
    mStream << string::joinValues(paramNames, ",") << ") = " << expr->expression()->accept(*this);
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue PrintVisitor::visit(ast::exprs::AssignmentExpression* expr) {
    mStream << string::wStringToString(expr->identifier().text()) << " := ";
    expr->expression()->accept(*this);
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue PrintVisitor::visit(ast::exprs::OperatorExpression* expr) {
    expr->leftExpression()->accept(*this);
    mStream << " " << TokenTypeToString(expr->operation().type()) << " ";
    expr->rightExpression()->accept(*this);
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue PrintVisitor::visit(ast::exprs::SetExpression* expr) {
    mStream << "{";
    auto valuesSize = expr->values().size();
    std::for_each(expr->values().begin(), expr->values().end(), [&, idx = 0](const auto& value) mutable {
      value->accept(*this);
      if (idx++ < valuesSize - 1) {
        mStream << ", ";
      }
    });
    mStream << "}";
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue PrintVisitor::visit(ast::exprs::LiteralExpression* expr) {
    mStream << expr->value()->str();
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue PrintVisitor::visit(ast::exprs::GroupExpression* expr) {
    mStream << "(";
    expr->expression()->accept(*this);
    mStream << ")";
    return nullptr;
  }

  ast::NodeVisitor::VisitorRetValue PrintVisitor::visit(ast::exprs::VariableExpression* expr) {
    mStream << string::wStringToString(expr->token().text());
    return nullptr;
  }

}  // namespace em::utils
