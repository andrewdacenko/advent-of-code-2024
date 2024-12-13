#include "trail.hpp"

#include <queue>
#include <unordered_set>

namespace trail {
std::vector<Pos> getStartCoordinates(const std::vector<std::string> &grid) {
  std::vector<Pos> heads;
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].size(); ++j) {
      if (grid[i][j] == '0') {
        heads.push_back({i, j, 0});
      }
    }
  }

  return heads;
}

int countTrails(const std::vector<std::string> &grid, bool second) {
  auto heads = getStartCoordinates(grid);
  int directions[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
  int res = 0;
  for (auto head : heads) {
    int trails = 0;
    std::unordered_set<Pos, Pos::Hash> visited = {head};
    std::queue<Pos> queue({head});
    while (queue.size() != 0) {
      auto top = queue.front();
      queue.pop();
      for (auto next : directions) {
        Pos newTop = {top.row + next[0], top.col + next[1]};
        if (!(newTop.col >= 0 && newTop.row >= 0 && newTop.row < grid.size() &&
              newTop.col < grid[0].size())) {
          continue;
        }

        newTop.val = grid[newTop.row][newTop.col] - '0';
        if (visited.contains(newTop)) {
          continue;
        }

        if (newTop.val - top.val != 1) {
          continue;
        }

        visited.insert(newTop);
        if (newTop.val == 9) {
          trails++;
          continue;
        }

        queue.push(newTop);
      }
    }
    res += trails;
  }

  return res;
}
} // namespace trail