#include "fences.hpp"

#include <functional>
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

  int walls() const {
    int top, bottom = points.begin()->first;
    int left, right = points.begin()->second;

    for (auto p : points) {
      top = std::min(top, p.first);
      bottom = std::max(bottom, p.first);
      left = std::min(left, p.second);
      right = std::max(right, p.second);
    }

    int topWalls = wallsCount(
        top, bottom, (int[3]){1, -1, 0}, [](const Pos &p) { return p.first; },
        [](const Pos &a, const Pos &b) { return a.second < b.second; },
        [](const Pos &a, const Pos &b) { return a.second - b.second; });
    int bottomWalls = wallsCount(
        bottom, top, (int[3]){-1, 1, 0}, [](const Pos &p) { return p.first; },
        [](const Pos &a, const Pos &b) { return a.second < b.second; },
        [](const Pos &a, const Pos &b) { return a.second - b.second; });
    int leftWalls = wallsCount(
        left, right, (int[3]){1, 0, -1}, [](const Pos &p) { return p.second; },
        [](const Pos &a, const Pos &b) { return a.first < b.first; },
        [](const Pos &a, const Pos &b) { return a.first - b.first; });
    int rightWalls = wallsCount(
        right, left, (int[3]){-1, 0, 1}, [](const Pos &p) { return p.second; },
        [](const Pos &a, const Pos &b) { return a.first < b.first; },
        [](const Pos &a, const Pos &b) { return a.first - b.first; });

    return topWalls + bottomWalls + leftWalls + rightWalls;
  };

  int wallsCount(int from, int to, int delta[3],
                 std::function<int(const Pos &)> accessor,
                 std::function<bool(const Pos &, const Pos &)> sort,
                 std::function<int(const Pos &, const Pos &)> diff) const {
    int count = 0;
    for (int i = from; i != to + delta[0]; i += delta[0]) {
      std::vector<Pos> line;
      for (auto p : points) {
        if (accessor(p) == i &&
            !points.contains({p.first + delta[1], p.second + delta[2]})) {
          line.push_back(p);
        }
      }

      if (line.size() == 0) {
        continue;
      }

      std::sort(line.begin(), line.end(), sort);

      int splits = 1;
      for (int j = 0; j < line.size() - 1; j++) {
        if (diff(line[j + 1], line[j]) != 1) {
          splits++;
        }
      }

      count += splits;
    }

    return count;
  }

  int price(bool second) const {
    return points.size() * (second ? walls() : perimeter());
  }
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
      [second](auto acc, auto region) { return acc + region.price(second); });
}
} // namespace fences
