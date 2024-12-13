#pragma once

#include <functional>
#include <string>
#include <vector>

namespace trail {
struct Pos {
  int row;
  int col;
  int val;

  bool operator==(const Pos &other) const {
    return row == other.row && col == other.col;
  }

  struct Hash {
    std::size_t operator()(const Pos &pos) const {
      std::size_t h1 = std::hash<int>{}(pos.row);
      std::size_t h2 = std::hash<int>{}(pos.col);
      return h1 ^ (h2 << 1); // XOR and shift to combine hashes
    }
  };
};

int countTrails(const std::vector<std::string> &grid, bool second);
} // namespace trail