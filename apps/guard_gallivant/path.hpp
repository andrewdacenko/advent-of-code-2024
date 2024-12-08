#include <string>
#include <unordered_set>
#include <vector>

namespace path {

struct Pos {
  int row, col;
  // Equality operator for hashing and comparisons
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

enum Direction { Up, Down, Left, Right };

using Positions = std::unordered_set<Pos, Pos::Hash>;

int countMoves(const std::vector<std::string> &grid);
} // namespace path
