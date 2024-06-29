#include "Interpreter.h"

#include "../ast/exprs/AssignmentExpression.h"
#include "../ast/exprs/FunctionCall.h"
#include "../ast/exprs/FunctionDeclaration.h"
#include "../ast/exprs/GroupExpression.h"
#include "../ast/exprs/LiteralExpression.h"
#include "../ast/exprs/OperatorExpression.h"
#include "../ast/exprs/SetExpression.h"
#include "../ast/exprs/VariableExpression.h"
#include "../ast/stmts/ExpressionStatement.h"
#include "../utils/StringUtils.h"
#include "../values/LiteralValue.h"
#include "../values/functions/NativeFunction.h"
#include "../values/functions/ProgramFunction.h"
#include "../values/sets/MaterialSetValue.h"
#include "../values/sets/VirtualSetValue.h"

namespace em::runtime {
  Interpreter::Interpreter(std::shared_ptr<std::ostream> outputStream) : mOutputStream(std::move(outputStream)) {
    mVariables = {
        {L"ℝ", std::make_unique<values::sets::VirtualSetValue>(std::make_unique<values::functions::NativeFunction>(
                   L"ℝ",
                   [](const auto&) {
                     // TODO: Only return true if it's a number
                     return std::make_unique<values::LiteralValue<bool>>(true);
                   }))},
        {L"∅", std::make_unique<values::sets::MaterialSetValue>()},
        {L"print", std::make_unique<values::functions::NativeFunction>(
                       L"print", [this](const std::vector<std::shared_ptr<values::Value>>& args) {
                         *mOutputStream << args[0]->str() << '\n';
                         return std::make_unique<values::LiteralValue<int>>(0);
                       })}};
  }

  void Interpreter::execute(const std::unique_ptr<ast::Program>& program) {
    program->accept(*this);
  }

  void Interpreter::addVariable(const Token& token, const VisitorRetValue& value) {
    mVariables[token.text()] = value;
  }

  void Interpreter::visit(ast::Program* program) {
    for (const auto& stmt : program->statements()) {
      stmt->accept(*this);
    }
  }

  void Interpreter::visit(ast::stmts::ExpressionStatement* stmt) {
    auto res = stmt->expression()->accept(*this);
  }

  ast::NodeVisitor::VisitorRetValue Interpreter::visit(ast::exprs::FunctionDeclaration* expr) {
    auto function = std::make_shared<values::functions::ProgramFunction>(expr->identifier(), expr->parameters(),
                                                                         expr->expression());
    addVariable(expr->identifier(), function);
    return function;
  }

  ast::NodeVisitor::VisitorRetValue Interpreter::visit(ast::exprs::AssignmentExpression* expr) {
    auto value = expr->expression()->accept(*this);
    addVariable(expr->identifier(), value);
    return value;
  }

  Interpreter::VisitorRetValue Interpreter::visit(ast::exprs::OperatorExpression* expr) {
    auto leftValue = expr->leftExpression()->accept(*this);
    auto rightValue = expr->rightExpression()->accept(*this);
    // todo: study type checking here: require(Set)
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
    auto setValue = std::make_unique<values::sets::MaterialSetValue>();
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
    const auto& text = expr->token().text();
    auto it = mVariables.find(text);
    if (it != mVariables.cend()) {
      return it->second;
    }
    throw std::logic_error("Undefined identifier '" + utils::string::wStringToString(text) + "'");
  }

  ast::NodeVisitor::VisitorRetValue Interpreter::visit(ast::exprs::FunctionCall* expr) {
    auto function = expr->expression()->accept(*this);
    if (auto* functionValue = dynamic_cast<values::functions::Function*>(function.get())) {
      std::vector<VisitorRetValue> args;
      args.reserve(expr->arguments().size());
      std::transform(expr->arguments().cbegin(), expr->arguments().cend(), std::back_inserter(args),
                     [this](const auto& argExpr) { return argExpr->accept(*this); });
      return functionValue->execute(*this, args);
    } else {
      throw std::logic_error("Invalid function call target '" + function->str() + "'");
    }
  }

}  // namespace em::runtime
