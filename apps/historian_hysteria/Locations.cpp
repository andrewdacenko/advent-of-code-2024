#include "Locations.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <regex>
#include <stdexcept>
#include <stdio.h>

namespace {
std::regex PATTERN(R"(\b(\d+)\s+(\d+)\b)");
} // namespace

namespace locations {

const int compareLocations(const LocationsLists &lists) {
  if (lists.first.size() != lists.second.size()) {
    throw std::runtime_error("Lists have different size");
  }

  auto first = lists.first;
  auto second = lists.second;
  std::sort(first.begin(), first.end());
  std::sort(second.begin(), second.end());
  int diff = 0;
  for (int i = 0; i < first.size(); i++) {
    auto distance = std::abs(first[i] - second[i]);
    diff += distance;
  }
  return diff;
}

const LocationsLists getLocations(const std::string &filePath) {
  std::filesystem::path path(filePath);
  if (!std::filesystem::is_regular_file(path)) {
    throw std::filesystem::filesystem_error("File not found",
                                            std::error_code());
  }

  std::ifstream file(filePath);
  if (!file.good()) {
    throw std::ios_base::failure("Could not open file");
  }

  Locations firstList;
  Locations secondList;
  std::string line;
  std::smatch matches;
  while (std::getline(file, line)) {
    if (std::regex_match(line, matches, PATTERN)) {
      firstList.push_back(std::stoi(matches[1]));
      secondList.push_back(std::stoi(matches[2]));
    } else {
      throw std::runtime_error("Failed to parse line: " + line);
    }
  }

  return {firstList, secondList};
}

} // namespace locations