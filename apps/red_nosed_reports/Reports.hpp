#pragma once

#include <string>
#include <vector>

namespace reports {

enum Direction { INCREASING, DECREASING };

using Report = std::vector<int>;
using Reports = std::vector<Report>;

const Reports getReports(const std::string &filePath);
const int countSafeReports(const Reports &reports);

} // namespace reports