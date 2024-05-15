#include <iostream>

#include "em/Lexer.h"
#include "em/Parser.h"
#include "em/runtime/Interpreter.h"
#include "em/utils/PrintVisitor.h"

int main() {
  std::wstring source =
      L"set := {1, 2, 3, 4}\n"
      "set ⊆ ℝ\n"
      "1 ∈ set\n"
      "5 ∈ set";
  auto lexer = em::Lexer(source);
  auto tokens = lexer.scanTokens();
  std::cout << "Scanned " << tokens.size() << " tokens!: ";
  std::for_each(tokens.cbegin(), tokens.cend(), [&](const auto& token) { std::cout << token << ", "; });
  std::cout << '\n';

  auto parser = em::Parser(tokens);
  auto program = parser.parse();

  auto printer = em::utils::PrintVisitor();
  std::cout << printer.print(program) << '\n';

  auto interpreter = em::runtime::Interpreter();
  interpreter.execute(program);

  return 0;
}
