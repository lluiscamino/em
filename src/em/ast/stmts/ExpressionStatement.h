#pragma once
#include "../exprs/Expression.h"
#include "Statement.h"

namespace em::ast::stmts {

  class ExpressionStatement : public Statement {
   public:
    explicit ExpressionStatement(std::unique_ptr<exprs::Expression> expression);

    [[nodiscard]] const std::unique_ptr<exprs::Expression>& expression() const;

    void accept(NodeVisitor& visitor) override;

   private:
    std::unique_ptr<exprs::Expression> mExpression;
  };

}  // namespace em::ast::stmts
