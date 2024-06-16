#include "../../../src/em/EmLang.h"
#include "../../../src/em/runtime/Interpreter.h"
#include "../../utils/TestUtils.h"

namespace {
  const std::filesystem::path SNAPSHOTS_PATH = std::filesystem::path(__FILE__).parent_path() / "snapshots";
  const std::string INPUT_FILES_NAME = "program.em";
  const std::string EXPECTED_OUTPUT_FILES_NAME = "expected_output.txt";
}  // namespace

int main() {
  test::utils::runSnapshotTests(SNAPSHOTS_PATH, INPUT_FILES_NAME, EXPECTED_OUTPUT_FILES_NAME, [](const auto& input) {
    auto outputStream = std::make_shared<std::stringstream>();
    em::EmLang::runProgram(input, outputStream);
    return em::utils::string::stringToWstring(outputStream->str());
  });
}