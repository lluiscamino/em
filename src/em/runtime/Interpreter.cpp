#include "Interpreter.h"

#include "../ast/exprs/AssignmentExpression.h"
#include "../ast/exprs/FunctionDeclaration.h"
#include "../ast/exprs/GroupExpression.h"
#include "../ast/exprs/LiteralExpression.h"
#include "../ast/exprs/OperatorExpression.h"
#include "../ast/exprs/SetExpression.h"
#include "../ast/exprs/VariableExpression.h"
#include "../ast/stmts/ExpressionStatement.h"
#include "../values/LiteralValue.h"
#include "../values/MaterialSetValue.h"
#include "../values/VirtualSetValue.h"
#include "../values/functions/ProgramFunction.h"

namespace em::runtime {
  Interpreter::Interpreter() {
    mVariables = {
        {L"ℝ", std::make_unique<values::VirtualSetValue>(std::make_unique<ast::exprs::LiteralExpression>(
                   std::make_unique<values::LiteralValue<bool>>(true)))},
        {L"∅", std::make_unique<values::VirtualSetValue>(std::make_unique<ast::exprs::LiteralExpression>(
                   std::make_unique<values::LiteralValue<bool>>(false)))},
    };
  }

  void Interpreter::execute(const std::unique_ptr<ast::Program>& program) {
    program->accept(*this);
  }

  void Interpreter::visit(ast::Program* program) {
    for (const auto& stmt : program->statements()) {
      stmt->accept(*this);
    }
  }

  void Interpreter::visit(ast::stmts::ExpressionStatement* stmt) {
    auto res = stmt->expression()->accept(*this);
    std::cout << "Expr:\t" << res->str() << '\n';
  }

  ast::NodeVisitor::VisitorRetValue Interpreter::visit(ast::exprs::FunctionDeclaration* expr) {
    auto function = std::make_shared<values::ProgramFunction>(expr->identifier(), expr->expression());
    mVariables[expr->identifier().text()] = function;
    return function;
  }

  ast::NodeVisitor::VisitorRetValue Interpreter::visit(ast::exprs::AssignmentExpression* expr) {
    auto value = expr->expression()->accept(*this);
    mVariables[expr->identifier().text()] = value;
    return value;
  }

  Interpreter::VisitorRetValue Interpreter::visit(ast::exprs::OperatorExpression* expr) {
    auto leftValue = expr->leftExpression()->accept(*this);
    auto rightValue = expr->rightExpression()->accept(*this);
    switch (expr->operation().type()) {
      case TokenType::EQUAL:
        return leftValue->isEqualTo(rightValue);
      case TokenType::NOT_EQUAL:
        return leftValue->isDifferentTo(rightValue);
      case TokenType::ELEMENT_OF:
        return leftValue->isElementOf(rightValue);
      case TokenType::UNION:
        return leftValue->unionOp(rightValue);
      case TokenType::INTERSECTION:
        return leftValue->intersection(rightValue);
      case TokenType::SUBSET:
        return leftValue->isSubsetOf(rightValue);
      case TokenType::NOT_SUBSET:
        return leftValue->isNotSubsetOf(rightValue);
      default:
        throw std::logic_error("Operation " + TokenTypeToString(expr->operation().type()) +
                               " is not supported for a operator expression");
    }
  }

  Interpreter::VisitorRetValue Interpreter::visit(ast::exprs::SetExpression* expr) {
    auto setValue = std::make_unique<values::MaterialSetValue>();
    std::for_each(expr->values().cbegin(), expr->values().cend(),
                  [&](const auto& subExpr) { setValue->addValue(subExpr->accept(*this)); });
    return setValue;
  }

  Interpreter::VisitorRetValue Interpreter::visit(ast::exprs::LiteralExpression* expr) {
    return expr->value();
  }

  ast::NodeVisitor::VisitorRetValue Interpreter::visit(ast::exprs::GroupExpression* expr) {
    return expr->expression()->accept(*this);
  }

  ast::NodeVisitor::VisitorRetValue Interpreter::visit(ast::exprs::VariableExpression* expr) {
    return mVariables[expr->token().text()];
  }

}  // namespace em::runtime
