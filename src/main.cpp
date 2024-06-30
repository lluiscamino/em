#include <codecvt>
#include <fstream>
#include <iostream>

#include "em/EmLang.h"
#include "em/utils/FileUtils.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Please specify program.txt path as the only argument!";
    return EXIT_FAILURE;
  }

  try {
    em::EmLang::runProgram(em::utils::file::getFileContents(argv[1]));
  } catch (const std::exception& exception) {
    std::cerr << exception.what();
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
