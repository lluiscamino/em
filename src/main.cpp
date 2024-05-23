#include <iostream>

#include <chrono>
#include <filesystem>

#include "em/Lexer.h"
#include "em/Parser.h"
#include "em/runtime/Interpreter.h"
#include "em/utils/AstTreeDiagramGenerator.h"
#include "em/utils/PrintVisitor.h"

void executeProgram() {
  std::wstring source = L"set := {fun1(x,y) = {1, 2, 3, 4}}\nfun2() = 1\n{fun1, fun1, fun2}";
  auto lexer = em::Lexer(source);
  auto tokens = lexer.scanTokens();
  std::cout << "Scanned " << tokens.size() << " tokens!: ";
  std::for_each(tokens.cbegin(), tokens.cend(), [&](const auto& token) { std::cout << token << ", "; });
  std::cout << '\n';

  auto parser = em::Parser(tokens);
  auto program = parser.parse();

  auto printer = em::utils::PrintVisitor();
  std::cout << printer.print(program) << '\n';

  auto astTreeDiagramGenereator = em::utils::AstTreeDiagramGenerator();
  astTreeDiagramGenereator.generate(program, std::filesystem::current_path() / "ast.dot");

  auto interpreter = em::runtime::Interpreter();
  interpreter.execute(program);
}

int main() {
  using namespace std::chrono;
  auto start = high_resolution_clock::now();
  executeProgram();
  auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
  std::cout << "Executed in " << duration.count() << " microseconds!";
  return 0;
}
