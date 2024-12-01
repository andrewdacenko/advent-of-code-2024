#pragma once

#include <string>
#include <utility>
#include <vector>

namespace locations {

using Locations = std::vector<int>;
using LocationsLists = std::pair<Locations, Locations>;

const int compareLocations(const LocationsLists &lists);
const int computeSimilarity(const LocationsLists &lists);
const LocationsLists getLocations(const std::string &filePath);

} // namespace locations