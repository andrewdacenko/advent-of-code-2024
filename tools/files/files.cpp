#include "files.hpp"
#include <fstream>
#include <ranges>

namespace files {
std::string getContent(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::ios_base::failure("Could not open file " + filename);
  }

  return {std::istreambuf_iterator(file), {}};
}

std::vector<std::string> getLines(const std::string& filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::ios_base::failure("Could not open file " + filename);
  }

  return {std::ranges::istream_view<std::string>(file) |
          std::ranges::to<std::vector<std::string>>()};
}
} // namespace files
