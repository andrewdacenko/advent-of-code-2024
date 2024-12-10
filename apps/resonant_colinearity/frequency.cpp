#include "frequency.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iterator>
#include <numeric>
#include <unordered_set>
#include <vector>

namespace frequency {
struct PairHash {
  size_t operator()(const std::pair<int, int> &p) const {
    return std::hash<int>{}(p.first) ^ std::hash<int>{}(p.second);
  }
};

NodesMap findNodesMap(const Grid &grid) {
  NodesMap nodesMap{};
  for (auto i = 0; i < grid.size(); ++i) {
    for (auto j = 0; j < grid.size(); ++j) {
      auto key = grid[i][j];
      if (key == '.') {
        continue;
      }

      if (!nodesMap.contains(key)) {
        nodesMap.insert({key, {}});
      }
      nodesMap[key].push_back({i, j});
    }
  }
  return nodesMap;
}

std::vector<PosPair> combinations(const std::vector<Pos> &nodes) {
  std::vector<PosPair> result;

  for (int i = 0; i < nodes.size() - 1; i++) {
    for (int j = i + 1; j < nodes.size(); j++) {
      result.push_back({nodes[i], nodes[j]});
    }
  }

  return result;
}

int countAntinodes(const Grid &grid) {
  auto nodesMap = findNodesMap(grid);
  auto pairs = std::accumulate(std::begin(nodesMap), std::end(nodesMap),
                               std::vector<PosPair>{},
                               [](auto acc, const NodesMap::value_type &v) {
                                 acc.append_range(combinations(v.second));
                                 return acc;
                               });

  auto inbounds = [&grid](const Pos &pos) -> bool {
    return pos.first >= 0 && pos.second >= 0 && pos.first < grid.size() &&
           pos.second < grid[0].size();
  };

  auto genAntinodes = [&inbounds](const PosPair &pair) {
    std::vector<Pos> res;

    auto [left, right] = pair;
    if (auto first =
            Pos{2 * left.first - right.first, 2 * left.second - right.second};
        inbounds(first)) {
      res.push_back(first);
    };

    if (auto second =
            Pos{2 * right.first - left.first, 2 * right.second - left.second};
        inbounds(second)) {
      res.push_back(second);
    }

    return res;
  };

  auto antinodes = std::accumulate(
      pairs.begin(), pairs.end(), std::unordered_set<Pos, PairHash>{},
      [&genAntinodes](auto acc, const PosPair &pair) {
        auto nodes = genAntinodes(pair);
        std::copy(nodes.begin(), nodes.end(), std::inserter(acc, acc.end()));
        return acc;
      });

  return antinodes.size();
}
} // namespace frequency
