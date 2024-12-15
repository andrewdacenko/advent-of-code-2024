#include "warehouse.hpp"
#include <numeric>
#include <optional>
#include <print>

namespace warehouse {
Warehouse::Warehouse(const std::vector<std::string> &grid, bool second)
    : second_(second) {
  cols_ = grid[0].size();
  for (int i = 0; i < grid.size(); ++i) {
    if (grid[i].contains("^") || grid[i].contains("<") ||
        grid[i].contains(">") || grid[i].contains("v")) {
      if (rows_ == 0) {
        rows_ = i - 1;
      }
      moves_ += grid[i];
      continue;
    }

    for (int j = 0; j < grid[i].length(); ++j) {
      if (grid[i][j] == '#') {
        walls_.insert({i, j});
      }
      if (grid[i][j] == 'O') {
        boxes_.insert({i, j});
      }
      if (grid[i][j] == '@') {
        robot_ = Pos{i, j};
      }
    }
  }
}

std::optional<Pos> Warehouse::nextEmptyPos(char move) const {
  auto [row, col] = dirs.at(move);
  auto next = Pos{row + robot_.row, col + robot_.col};
  while (!walls_.contains(next)) {
    if (!boxes_.contains(next)) {
      return next;
    }

    next = Pos{row + next.row, col + next.col};
  }

  if (walls_.contains(next) || boxes_.contains(next)) {
    return std::nullopt;
  }

  return next;
}

int Warehouse::countGPS() {
  for (const auto &move : moves_) {
    print("Move: {}\n", move);
    if (auto next = nextEmptyPos(move); next.has_value()) {
      auto [row, col] = dirs.at(move);
      if (!(next->row == robot_.row + row && next->col == robot_.col + col)) {
        boxes_.erase({robot_.row + row, robot_.col + col});
        boxes_.insert({next->row, next->col});
      }
      robot_.row += row;
      robot_.col += col;
    }

    printWarehouse();
    print("\n");
  }

  return std::accumulate(
      boxes_.begin(), boxes_.end(), 0,
      [](auto acc, auto pos) { return acc + 100 * pos.row + pos.col; });
}

template <class... _Args>
void Warehouse::print(std::format_string<_Args...> __fmt,
                      _Args &&...__args) const {
  if (!debug) {
    return;
  }

  return std::print(__fmt, std::forward<_Args>(__args)...);
}

void Warehouse::printWarehouse() const {
  for (int row = 0; row < rows_; ++row) {
    for (char col = 0; col < cols_; ++col) {
      if (walls_.contains({row, col})) {
        print("\033[0;31m#\033[0m");
      } else if (boxes_.contains({row, col})) {
        print("\033[0;33mO\033[0m");
      } else if (robot_.row == row && robot_.col == col) {
        print("\033[1;34m@\033[0m");
      } else {
        print(".");
      }
    }
    print("\n");
  }
}
} // namespace warehouse
