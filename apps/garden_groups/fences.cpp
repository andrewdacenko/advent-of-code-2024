#include "fences.hpp"

#include <iterator>
#include <numeric>
#include <print>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace fences {
constexpr int sides[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

using Pos = std::pair<int, int>;

struct PosHash {
  std::size_t operator()(const Pos &pos) const {
    std::size_t h1 = std::hash<int>{}(pos.first);
    std::size_t h2 = std::hash<int>{}(pos.second);
    return h1 ^ (h2 << 1); // XOR and shift to combine hashes
  }
};

struct Region {
  char symbol;
  std::unordered_set<Pos, PosHash> points;

  int perimeter() const {
    return std::accumulate(
        points.begin(), points.end(), 0, [this](auto acc, auto pos) {
          return acc + std::accumulate(
                           std::begin(sides), std::end(sides), 0,
                           [this, &pos](auto n, auto side) {
                             return n + (points.contains({pos.first + side[0],
                                                          pos.second + side[1]})
                                             ? 0
                                             : 1);
                           });
        });
  };

  int price() const { return points.size() * perimeter(); }
};

int countFences(const std::vector<std::string> &grid, bool second) {
  std::unordered_set<Pos, PosHash> visited;
  std::vector<Region> regions;

  auto inbounds = [&grid](const Pos &pos) {
    return pos.first >= 0 && pos.second >= 0 && pos.first < grid.size() &&
           pos.second < grid[0].size();
  };

  auto region = [&](int row, int col) -> Region {
    Region region{grid[row][col], {}};
    std::queue<Pos> queue({{row, col}});
    while (queue.size()) {
      auto v = queue.front();
      queue.pop();
      if (visited.contains(v)) {
        continue;
      }

      if (grid[v.first][v.second] != region.symbol) {
        continue;
      }

      region.points.insert(v);
      visited.insert(v);
      for (auto side : sides) {
        if (Pos next = {v.first + side[0], v.second + side[1]};
            inbounds(next)) {
          queue.push(next);
        }
      }
    }

    return region;
  };

  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].length(); ++j) {
      if (visited.contains(Pos(i, j))) {
        continue;
      }

      regions.push_back(region(i, j));
    }
  }

  return std::accumulate(
      regions.begin(), regions.end(), 0,
      [](auto acc, auto region) { return acc + region.price(); });
}
} // namespace fences
