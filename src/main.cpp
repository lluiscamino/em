#include <iostream>

#include <chrono>
#include <filesystem>

#include "em/Lexer.h"
#include "em/Parser.h"
#include "em/runtime/Interpreter.h"
#include "em/utils/AstTreeDiagramGenerator.h"

void executeProgram() {
  std::wstring source = L"a := {3} ∪ {4}\nb:={3} ∪ {4}\nc:=a∪a\nprint(c)";

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
