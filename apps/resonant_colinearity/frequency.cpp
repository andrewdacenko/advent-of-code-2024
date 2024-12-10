#include "frequency.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iterator>
#include <numeric>
#include <vector>

namespace frequency {

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

int countAntinodes(const Grid &grid, bool second) {
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

  int lim = second ? grid.size() : 1;

  auto genAntinodes = [lim, &inbounds](const PosPair &pair) {
    std::vector<Pos> res;

    auto [left, right] = pair;
    for (int i = 1; i <= lim; i++) {
      if (auto pos = Pos{left.first - i * (right.first - left.first),
                         left.second - i * (right.second - left.second)};
          inbounds(pos)) {
        res.push_back(pos);
      } else {
        break;
      }
    }

    for (int i = 1; i <= lim; i++) {
      if (auto second = Pos{right.first - i * (left.first - right.first),
                            right.second - i * (left.second - right.second)};
          inbounds(second)) {
        res.push_back(second);
      }
    }

    return res;
  };

  auto accAntinodes = [&genAntinodes](const std::vector<PosPair>& pairs) {
    return std::accumulate(
      pairs.begin(), pairs.end(), UniquePositions{},
      [&genAntinodes](auto acc, const PosPair &pair) {
        auto nodes = genAntinodes(pair);
        std::copy(nodes.begin(), nodes.end(), std::inserter(acc, acc.end()));
        return acc;
      });
  };

  auto antinodes = accAntinodes(pairs);

  if (second) {
    auto antinodePairs = combinations({antinodes.begin(), antinodes.end()});
    for (auto node: accAntinodes(antinodePairs)) {
      if (grid[node.first][node.second] != '.') {
        antinodes.insert(node);
      }
    }
  }

  return antinodes.size();
}
} // namespace frequency
