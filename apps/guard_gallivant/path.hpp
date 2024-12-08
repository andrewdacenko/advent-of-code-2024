#include <string>
#include <unordered_set>
#include <vector>

namespace path {

struct Pos {
  int row, col;

  bool inbounds(const std::vector<std::string> &grid) const {
    return row > 0 && row < grid.size() && col > 0 && col < grid[0].size();
  }

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

struct Move {
  Pos pos;
  Direction dir;

  bool operator==(const Move &other) const {
    return pos == other.pos && dir == other.dir;
  }

  struct Hash {
    std::size_t operator()(const Move &move) const {
      std::size_t h1 = Pos::Hash{}(move.pos);
      std::size_t h2 = std::hash<int>{}(move.dir);
      return h1 ^ (h2 << 1); // XOR and shift to combine hashes
    }
  };
};

using Positions = std::unordered_set<Pos, Pos::Hash>;
using Moves = std::unordered_set<Move, Move::Hash>;

Moves getMoves(const std::vector<std::string> &grid);
int countMoves(const std::vector<std::string> &grid);
int countLoops(const std::vector<std::string> &grid);
} // namespace path
