#include "EmLang.h"

#include <fstream>

#include "Lexer.h"
#include "Parser.h"
#include "runtime/Interpreter.h"
#include "utils/AstTreeDiagramGenerator.h"

namespace em {
void EmLang::runProgram(const std::wstring& program,
                        const std::shared_ptr<std::ostream>& outputStream) {
  auto lexer = Lexer(program);
  auto tokens = lexer.scanTokens();

  auto parser = Parser(tokens);
  auto ast = parser.parse();

  auto astTreeDiagramGenereator = utils::AstTreeDiagramGenerator();
  astTreeDiagramGenereator.generate(
      ast, std::filesystem::current_path() / "ast.dot");

  auto interpreter = runtime::Interpreter(outputStream);
  interpreter.execute(ast);
}
}  // namespace em