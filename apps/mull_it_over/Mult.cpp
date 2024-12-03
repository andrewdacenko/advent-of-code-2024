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
std::regex PATTERN(R"(mul\((\d+),(\d+)\))");
} // namespace

namespace mult {

Instructions parseInstructions(const std::string &filePath) {
  std::filesystem::path path(filePath);
  if (!std::filesystem::is_regular_file(path)) {
    throw std::filesystem::filesystem_error("File not found",
                                            std::error_code());
  }

  std::ifstream file(filePath);
  if (!file.is_open()) {
    throw std::ios_base::failure("Could not open file");
  }

  auto contents = std::string((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());

  std::sregex_iterator begin(contents.begin(), contents.end(), PATTERN);
  std::sregex_iterator end;

  Instructions instructions;
  for (std::sregex_iterator it = begin; it != end; ++it) {
    std::smatch match = *it;
    instructions.push_back(std::stoi(match[1]) * std::stoi(match[2]));
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