#include "path.hpp"

#include <stdexcept>

namespace path {

int countMoves(const std::vector<std::string> &grid) {
  Positions obstactles;
  Positions moves;
  Pos *guardPos = nullptr;

  for (int row = 0; row < grid.size(); ++row) {
    for (int col = 0; col < grid[row].length(); ++col) {
      if (grid[row][col] == '^') {
        guardPos = new Pos{row, col};
        moves.insert(*guardPos);
        continue;
      }

      if (grid[row][col] == '#') {
        obstactles.insert({row, col});
        continue;
      }
    }
  }

  auto isBlocked = [&obstactles](const Pos &pos) {
    return obstactles.find(pos) != obstactles.end();
  };

  Direction guardDir{Direction::Up};
  while (guardPos->row > 0 && guardPos->col > 0 &&
         guardPos->row < grid.size() && guardPos->col < grid[0].size()) {
    switch (guardDir) {
    case Direction::Up:
      if (isBlocked({guardPos->row - 1, guardPos->col}))
        guardDir = Direction::Right;
      else
        guardPos->row -= 1;
      break;

    case Direction::Down:
      if (isBlocked({guardPos->row + 1, guardPos->col}))
        guardDir = Direction::Left;
      else
        ++guardPos->row;
      break;

    case Direction::Left:
      if (isBlocked({guardPos->row, guardPos->col - 1}))
        guardDir = Direction::Up;
      else
        --guardPos->col;
      break;

    case Direction::Right:
      if (isBlocked({guardPos->row, guardPos->col + 1}))
        guardDir = Direction::Down;
      else
        ++guardPos->col;
      break;
    }

    moves.insert(*guardPos);
  }

  return moves.size() - 1;
}
} // namespace path
