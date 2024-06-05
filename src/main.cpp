#include <iostream>

#include <chrono>
#include <filesystem>

#include "em/Lexer.h"
#include "em/Parser.h"
#include "em/runtime/Interpreter.h"
#include "em/utils/AstTreeDiagramGenerator.h"

void executeProgram() {
  std::wstring source =
      L"generator(x) = f(x) = print(x)\n"
      "set := {fun1(x) = x, fun2(x) = x}\n"
      "a:= fun1 ∈ set\n"
      "gf := generator(3)\n"
      "print(gf)\n"
      "gf(ℝ)\n";

  auto lexer = em::Lexer(source);
  auto tokens = lexer.scanTokens();

  auto parser = em::Parser(tokens);
  auto program = parser.parse();

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
  std::cout << "\nExecuted in " << duration.count() << " microseconds!";
  return 0;
}
