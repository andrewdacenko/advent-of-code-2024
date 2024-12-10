#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace frequency {

using Pos = std::pair<int, int>;
using PosPair = std::pair<Pos, Pos>;
struct PosHash {
  size_t operator()(const std::pair<int, int> &p) const {
    return std::hash<int>{}(p.first) ^ std::hash<int>{}(p.second);
  }
};
using UniquePositions = std::unordered_set<Pos, PosHash>;
using NodesMap = std::unordered_map<char, std::vector<Pos>>;
using Grid = std::vector<std::string>;

NodesMap findNodesMap(const Grid &word);
std::vector<PosPair> combinations(const std::vector<Pos>& nodes);
int countAntinodes(const Grid &grid, bool second);
} // namespace frequency
