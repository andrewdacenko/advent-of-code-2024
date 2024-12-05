#pragma once

#include <string>
#include <vector>

namespace search {
struct Pos {
  int line;
  int index;
  int nextLine;
  int nextIndex;
};
std::vector<std::string> readFileLines(const std::string &filename);
int countWords(const std::vector<std::string> &lines);
int countCrossWords(const std::vector<std::string> &lines);
} // namespace search