cmake_minimum_required(VERSION 3.28)
project(em)

set(CMAKE_CXX_STANDARD 17)

add_library(Em
        src/em/Lexer.cpp
        src/em/Lexer.h
        src/em/Token.cpp
        src/em/Token.h
        src/em/Parser.cpp
        src/em/Parser.h
        src/em/ast/exprs/Expression.h
        src/em/values/Value.h
        src/em/ast/exprs/LiteralExpression.cpp
        src/em/ast/exprs/LiteralExpression.h
        src/em/ast/NodeVisitor.h
        src/em/ast/exprs/OperatorExpression.cpp
        src/em/ast/exprs/OperatorExpression.h
        src/em/ast/exprs/MaterialSetExpression.cpp
        src/em/ast/exprs/MaterialSetExpression.h
        src/em/runtime/Interpreter.cpp
        src/em/runtime/Interpreter.h
        src/em/values/LiteralValue.h
        src/em/values/sets/MaterialSetValue.cpp
        src/em/values/sets/MaterialSetValue.h
        src/em/ast/exprs/GroupExpression.cpp
        src/em/ast/exprs/GroupExpression.h
        src/em/values/Value.cpp
        src/em/ast/exprs/AssignmentExpression.cpp
        src/em/ast/exprs/AssignmentExpression.h
        src/em/ast/exprs/VariableExpression.cpp
        src/em/ast/exprs/VariableExpression.h
        src/em/utils/StringUtils.h
        src/em/values/sets/VirtualSetValue.cpp
        src/em/values/sets/VirtualSetValue.h
        src/em/ast/Node.h
        src/em/ast/stmts/Statement.h
        src/em/ast/stmts/ExpressionStatement.cpp
        src/em/ast/stmts/ExpressionStatement.h
        src/em/ast/Program.cpp
        src/em/ast/Program.h
        src/em/ast/exprs/FunctionDeclaration.cpp
        src/em/ast/exprs/FunctionDeclaration.h
        src/em/utils/AstTreeDiagramGenerator.cpp
        src/em/utils/AstTreeDiagramGenerator.h
        src/em/values/functions/Function.h
        src/em/values/functions/ProgramFunction.cpp
        src/em/values/functions/ProgramFunction.h
        src/em/ast/exprs/FunctionCall.cpp
        src/em/ast/exprs/FunctionCall.h
        src/em/values/functions/NativeFunction.cpp
        src/em/values/functions/NativeFunction.h
        src/em/values/functions/Function.cpp
        src/em/values/sets/Set.cpp
        src/em/values/sets/Set.h
        src/em/EmLang.cpp
        src/em/EmLang.h
        src/em/utils/FileUtils.h
        src/em/ast/exprs/VirtualSetExpression.cpp
        src/em/ast/exprs/VirtualSetExpression.h
)

add_executable(main src/main.cpp)
target_link_libraries(main Em)

add_executable(test
        test/snapshot/EmLang/main.cpp
        test/utils/TestUtils.h
        test/snapshot/EmLang/main.cpp
)
target_link_libraries(test Em)