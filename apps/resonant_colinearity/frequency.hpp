#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace frequency {

using Pos = std::pair<int, int>;
using PosPair = std::pair<Pos, Pos>;
using NodesMap = std::unordered_map<char, std::vector<Pos>>;
using Grid = std::vector<std::string>;

NodesMap findNodesMap(const Grid &word);
std::vector<PosPair> combinations(const std::vector<Pos>& nodes);
int countAntinodes(const Grid &grid);
} // namespace frequency
