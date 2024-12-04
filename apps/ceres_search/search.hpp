#pragma once

#include <vector>
#include <string>

namespace search {
struct Pos {
  int line;
  int index;
  int nextLine;
  int nextIndex;
};
std::vector<std::string> readFileLines(const std::string &filename);
int countWords(const std::vector<std::string>& lines);
} // namespace search