#pragma once

#include <string>
#include <vector>

namespace reports {

enum DumpenerMode { ON, OFF };
enum Direction { INCREASING, DECREASING };

using Report = std::vector<int>;
using Reports = std::vector<Report>;

const Reports getReports(const std::string &filePath);
int countSafeReports(const Reports &reports, DumpenerMode mode);
int getSafetyViolationIndex(const Report &report);
bool isReportSafeWithDampener(const Report &report);

} // namespace reports