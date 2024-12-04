#include "Mult.hpp"

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

namespace {
std::regex MULT_PATTERN(R"(mul\((\d+),(\d+)\)|do(n't)?\(\))");
} // namespace

namespace mult {

Instructions parseInstructions(const std::string &filePath, MultMode mode) {
  std::filesystem::path path(filePath);
  if (!std::filesystem::is_regular_file(path)) {
    throw std::filesystem::filesystem_error("File not found",
                                            std::error_code());
  }

  std::ifstream file(filePath);
  if (!file.is_open()) {
    throw std::ios_base::failure("Could not open file");
  }


  std::string line;
  bool enabled = true;
  Instructions instructions;
  while (std::getline(file, line)) {
    std::sregex_iterator begin(line.begin(), line.end(), MULT_PATTERN);
    std::sregex_iterator end;

    for (std::sregex_iterator it = begin; it != end; ++it) {
      std::smatch match = *it;
      std::string operation = match[0];
      if (operation == "do()") {
        enabled = true;
      } else if (operation == "don't()") {
        enabled = false;
      } else if (enabled || mode == MultMode::MULT_IT_OVER) {
        instructions.push_back(std::stoi(match[1]) * std::stoi(match[2]));
      }
    }
  }

  return instructions;
}

int calculate(const Instructions &instructions) {
  int result = 0;
  for (auto instruction : instructions) {
    result += instruction;
  }

  return result;
}

} // namespace mult