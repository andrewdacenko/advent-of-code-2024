#include "files.hpp"
#include <fstream>
#include <ranges>
#include <string>
#include <vector>

namespace files {
std::string getContent(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::ios_base::failure("Could not open file " + filename);
  }

  return {std::istreambuf_iterator(file), {}};
}

std::vector<std::string> getLines(const std::string &filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::ios_base::failure("Could not open file " + filename);
  }

  std::string line;
  std::vector<std::string> lines;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  return {lines};
};
} // namespace files
