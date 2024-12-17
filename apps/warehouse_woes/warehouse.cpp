#include "warehouse.hpp"
#include <numeric>
#include <optional>
#include <print>
#include <vector>

namespace warehouse {
Warehouse::Warehouse(const std::vector<std::string> &grid, bool second) {
  scale = second ? 2 : 1;
  cols_ = grid[0].size() * scale;
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
        walls_.insert({i, j * scale});
        if (scale == 2) {
          walls_.insert({i, j * scale + 1});
        }
      }
      if (grid[i][j] == 'O') {
        boxes_.insert({i, j * scale, scale});
      }
      if (grid[i][j] == '@') {
        robot_ = Pos{i, j * scale};
      }
    }
  }
}

bool Warehouse::canMove(const Pos &pos, char move) const {
  auto [row, col] = dirs.at(move);
  if (pos.width == 1) {
    if (walls_.contains({pos.row + row, pos.col + col}))
      return false;

    if (move == '<') {
      auto next = Pos{pos.row, pos.col - scale, scale};
      if (boxes_.contains(next)) {
        return canMove(next, move);
      }

      return true;
    }

    if (move == '>') {
      auto next = Pos{pos.row, pos.col + 1, scale};
      if (boxes_.contains(next)) {
        return canMove(next, move);
      }

      return true;
    }

    if (boxes_.contains({pos.row + row, pos.col, scale})) {
      return canMove({pos.row + row, pos.col, scale}, move);
    }

    if (scale == 2) {
      if (boxes_.contains({pos.row + row, pos.col - 1, scale})) {
        return canMove({pos.row + row, pos.col - 1, scale}, move);
      }
    }

    return true;
  }

  if (move == '<') {
    if (walls_.contains({pos.row, pos.col - 1}))
      return false;

    if (boxes_.contains({pos.row, pos.col - 2, scale})) {
      return canMove({pos.row, pos.col - 2, scale}, move);
    }

    return true;
  }

  if (move == '>') {
    if (walls_.contains({pos.row, pos.col + 2}))
      return false;

    if (boxes_.contains({pos.row, pos.col + 2, scale})) {
      return canMove({pos.row, pos.col + 2, scale}, move);
    }

    return true;
  }

  if (walls_.contains({pos.row + row, pos.col}) ||
      walls_.contains({pos.row + row, pos.col + 1})) {
    return false;
  }

  if (boxes_.contains({pos.row + row, pos.col, scale})) {
    return canMove({pos.row + row, pos.col, scale}, move);
  }

  auto left = Pos{pos.row + row, pos.col - 1, scale};
  auto right = Pos{pos.row + row, pos.col + 1, scale};
  if (boxes_.contains(left) && boxes_.contains(right)) {
    return canMove(left, move) && canMove(right, move);
  }

  if (boxes_.contains(left)) {
    return canMove(left, move);
  }

  if (boxes_.contains(right)) {
    return canMove(right, move);
  }

  return true;
}

std::vector<Pos> Warehouse::getHorizontalBoxes(const Pos &pos, char dir) {
  std::vector<Pos> boxes;
  auto [row, col] = dirs.at(dir);

  if (scale == 1) {
    Pos box = {pos.row + row, pos.col, scale};
    while (boxes_.contains(box)) {
      boxes.push_back(box);
      box.row += row;
    }
    return boxes;
  }

  if (boxes_.contains({pos.row + row, pos.col, scale})) {
    boxes.push_back({pos.row + row, pos.col, scale});
    boxes.append_range(
        getHorizontalBoxes({pos.row + row, pos.col, scale}, dir));
    return boxes;
  }

  Pos left{pos.row + row, pos.col - 1, scale};
  Pos right{pos.row + row, pos.col + 1, scale};
  if (boxes_.contains(left)) {
    boxes.push_back(left);
    boxes.append_range(getHorizontalBoxes(left, dir));
  }

  if (boxes_.contains(right)) {
    boxes.push_back(right);
    boxes.append_range(getHorizontalBoxes(right, dir));
  }

  return boxes;
};

int Warehouse::countGPS() {
  print("Start:\n");
  printWarehouse();
  print("\n");

  for (const auto &move : moves_) {
    print("Move: {}\n", move);
    if (canMove(robot_, move)) {
      auto [row, col] = dirs.at(move);
      if (move == '>' &&
          boxes_.contains({robot_.row, robot_.col + col, scale})) {
        if (scale == 2) {
          Pos box = {robot_.row, robot_.col + col, scale};
          Pos next = {robot_.row, robot_.col + col * scale, scale};
          std::vector<Pos> newBoxes = {};
          while (boxes_.contains(box)) {
            newBoxes.push_back(next);
            boxes_.erase(box);
            box.col += col * scale;
            next.col += col * scale;
          }
          boxes_.insert_range(newBoxes);
        } else {
          Pos box = {robot_.row, robot_.col + col, scale};
          Pos next = {robot_.row, robot_.col + col + col, scale};
          std::vector<Pos> newBoxes = {};
          while (boxes_.contains(box)) {
            newBoxes.push_back(next);
            boxes_.erase(box);
            box.col += col;
            next.col += col;
          }
          boxes_.insert_range(newBoxes);
        }
      }

      if (move == '<' &&
          boxes_.contains({robot_.row, robot_.col + col * scale, scale})) {
        if (scale == 2) {

          Pos box = {robot_.row, robot_.col + col * scale, scale};
          Pos next = {robot_.row, robot_.col + col * scale + col, scale};
          std::vector<Pos> newBoxes = {};
          while (boxes_.contains(box)) {
            newBoxes.push_back(next);
            boxes_.erase(box);
            box.col += col * scale;
            next.col += col * scale;
          }
          boxes_.insert_range(newBoxes);
        } else {
          Pos box = {robot_.row, robot_.col + col, scale};
          Pos next = {robot_.row, robot_.col + col + col, scale};
          std::vector<Pos> newBoxes = {};
          while (boxes_.contains(box)) {
            newBoxes.push_back(next);
            boxes_.erase(box);
            box.col += col;
            next.col += col;
          }
          boxes_.insert_range(newBoxes);
        }
      }

      if (col == 0 &&
          boxes_.contains({robot_.row + row, robot_.col + col, scale})) {
        auto boxes =
            getHorizontalBoxes({robot_.row, robot_.col + col, scale}, move);
        for (auto box : boxes) {
          boxes_.erase(box);
        }
        for (auto box : boxes) {
          boxes_.insert({box.row + row, box.col, scale});
        }
      }

      if (col == 0 && scale == 2 &&
          boxes_.contains({robot_.row + row, robot_.col + col - 1, scale})) {
        auto boxes =
            getHorizontalBoxes({robot_.row, robot_.col + col - 1, scale}, move);
        for (auto box : boxes) {
          boxes_.erase(box);
        }
        for (auto box : boxes) {
          boxes_.insert({box.row + row, box.col, scale});
        }
      }

      robot_.col += col;
      robot_.row += row;
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
      } else if (boxes_.contains({row, col, scale})) {
        print("\033[0;33m{}\033[0m", scale == 1 ? "O" : "[]");
      } else if (robot_.row == row && robot_.col == col) {
        print("\033[1;34m@\033[0m");
      } else if (scale == 2 && boxes_.contains({row, col - 1, scale})) {
        continue;
      } else {
        print(".");
      }
    }
    print("\n");
  }
}
} // namespace warehouse
