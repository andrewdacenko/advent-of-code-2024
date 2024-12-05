#include "search.hpp"

#include <cstdio>
#include <fstream>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

namespace search {
std::vector<std::string> readFileLines(const std::string &filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    return {};
  }

  return {std::ranges::istream_view<std::string>(file) |
          std::ranges::to<std::vector<std::string>>()};
}

int countWords(const std::vector<std::string> &lines) {
  int count = 0;
  int rows = lines.size();
  int columns = lines[0].size();

  auto getPositions = [&rows, &columns, &lines](int row, int col) {
    std::vector<Pos> positions;
    for (int line = -1; line <= 1; line++) {
      for (int index = -1; index <= 1; index++) {
        int nextIndex = col + index;
        int nextLine = row + line;

        if (line == 0 && index == 0) {
          continue;
        }

        if (nextIndex < 0 || nextIndex >= rows || nextLine < 0 ||
            nextLine >= columns) {
          continue;
        }

        positions.push_back({row, col, line, index});
      }
    }

    return positions;
  };

  auto getNextPostitions = [&lines, &rows, &columns](std::vector<Pos> positions,
                                                     char nextChar) {
    return std::accumulate(
        positions.begin(), positions.end(), std::vector<Pos>{},
        [&](std::vector<Pos> acc, Pos pos) {
          int nextIndex = pos.index + pos.nextIndex;
          int nextLine = pos.line + pos.nextLine;

          if (nextIndex < 0 || nextIndex >= rows || nextLine < 0 ||
              nextLine >= columns) {
            return acc;
          }

          if (lines[nextLine][nextIndex] != nextChar) {
            return acc;
          }

          acc.push_back({nextLine, nextIndex, pos.nextLine, pos.nextIndex});
          return acc;
        });
  };

  std::vector<Pos> x;
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < columns; ++col) {
      if (lines[row][col] == 'X') {
        x.append_range(getPositions(row, col));
      }
    }
  }

  auto m = getNextPostitions(x, 'M');
  auto a = getNextPostitions(m, 'A');
  auto s = getNextPostitions(a, 'S');

  return s.size();
}

int countCrossWords(const std::vector<std::string> &lines) {
  int count = 0;
  int rows = lines.size();
  int columns = lines[0].size();

  auto isValidXMAS = [&lines](int row, int col) {
    char tl = lines[row - 1][col - 1];
    char tr = lines[row - 1][col + 1];
    char bl = lines[row + 1][col - 1];
    char br = lines[row + 1][col + 1];

    char c[4] = {tl, tr, bl, br};
    for (auto ch : c) {
      if (ch != 'M' && ch != 'S') {
        return false;
      }
    }

    if (tl == br || tr == bl) {
      return false;
    }

    return true;
  };

  for (int row = 1; row < rows - 1; ++row) {
    for (int col = 1; col < columns - 1; ++col) {
      if (lines[row][col] == 'A' && isValidXMAS(row, col)) {
        count++;
      }
    }
  }

  return count;
}
} // namespace search