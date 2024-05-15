#pragma once

#include "../values/Value.h"

namespace em::ast {
  class Program;

  namespace stmts {
    class ExpressionStatement;
  }

  namespace exprs {
    class AssignmentExpression;

    class OperatorExpression;

    class SetExpression;

    class LiteralExpression;

    class GroupExpression;

    class VariableExpression;
  }  // namespace exprs

  class NodeVisitor {
   public:
    using VisitorRetValue =
        std::shared_ptr<values::Value>;  // TODO: Consider using const std::unique_ptr<values::Value> &

    virtual ~NodeVisitor() = default;

#pragma mark - Program
    virtual void visit(Program* program) = 0;  // TODO: return value should be void

#pragma mark - Statements
    virtual void visit(stmts::ExpressionStatement* stmt) = 0;

#pragma mark - Expressions
    virtual VisitorRetValue visit(exprs::AssignmentExpression* expr) = 0;

    virtual VisitorRetValue visit(exprs::OperatorExpression* expr) = 0;

    virtual VisitorRetValue visit(exprs::SetExpression* expr) = 0;

    virtual VisitorRetValue visit(exprs::LiteralExpression* expr) = 0;

    virtual VisitorRetValue visit(exprs::GroupExpression* expr) = 0;

    virtual VisitorRetValue visit(exprs::VariableExpression* expr) = 0;
  };
}  // namespace em::ast