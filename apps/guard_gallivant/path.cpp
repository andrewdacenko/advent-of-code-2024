#include "path.hpp"

#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace path {

Moves getMoves(const std::vector<std::string> &grid) {
  Positions obstactles;
  Moves moves;
  Move *guard = nullptr;

  for (int row = 0; row < grid.size(); ++row) {
    for (int col = 0; col < grid[row].length(); ++col) {
      if (grid[row][col] == '^') {
        guard = new Move{Pos{row, col}, Direction::Up};
        moves.insert(*guard);
        continue;
      }

      if (grid[row][col] == '#') {
        obstactles.insert({row, col});
        continue;
      }
    }
  }

  if (guard == nullptr) {
    throw std::runtime_error("Guard not found");
  }

  auto isBlocked = [&obstactles](const Pos &pos) {
    return obstactles.find(pos) != obstactles.end();
  };

  while (guard->pos.inbounds(grid)) {
    switch (guard->dir) {
    case Direction::Up:
      if (isBlocked({guard->pos.row - 1, guard->pos.col}))
        guard->dir = Direction::Right;
      else
        guard->pos.row -= 1;
      break;

    case Direction::Down:
      if (isBlocked({guard->pos.row + 1, guard->pos.col}))
        guard->dir = Direction::Left;
      else
        ++guard->pos.row;
      break;

    case Direction::Left:
      if (isBlocked({guard->pos.row, guard->pos.col - 1}))
        guard->dir = Direction::Up;
      else
        --guard->pos.col;
      break;

    case Direction::Right:
      if (isBlocked({guard->pos.row, guard->pos.col + 1}))
        guard->dir = Direction::Down;
      else
        ++guard->pos.col;
      break;
    }

    if (moves.contains(*guard)) {
      return moves;
    }

    moves.insert(*guard);
  }

  return moves;
}

int countMoves(const std::vector<std::string> &grid) {
  auto moves = getMoves(grid);

  Positions positions;
  std::transform(moves.begin(), moves.end(),
                 std::inserter(positions, positions.end()),
                 [](const Move &move) { return move.pos; });

  return positions.size() - 1;
}

int countLoops(const std::vector<std::string> &grid) {
  Pos *guardPos = nullptr;

  for (int row = 0; row < grid.size(); ++row) {
    for (int col = 0; col < grid[row].length(); ++col) {
      if (grid[row][col] == '^') {
        guardPos = new Pos{row, col};
        continue;
      }
    }
  }

  if (guardPos == nullptr) {
    throw std::runtime_error("Guard not found");
  }

  auto moves = getMoves(grid);

  Positions positions;
  std::transform(moves.begin(), moves.end(),
                 std::inserter(positions, positions.end()),
                 [](const Move &move) { return move.pos; });

  int loops = 0;
  for (auto &pos : positions) {
    if (pos == *guardPos) {
      continue;
    }

    std::vector<std::string> newGrid(grid);
    newGrid[pos.row][pos.col] = '#';

    auto moves = getMoves(newGrid);
    auto finish =
        std::count_if(moves.begin(), moves.end(), [&newGrid](const Move &move) {
          return !move.pos.inbounds(newGrid);
        });

    if (finish == 0) {
      loops++;
    }
  }

  return loops;
}
} // namespace path
