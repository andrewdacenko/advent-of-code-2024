#include "Reports.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <valarray>

namespace reports {

const Reports getReports(const std::string &filePath) {
  std::filesystem::path path(filePath);
  if (!std::filesystem::is_regular_file(path)) {
    throw std::filesystem::filesystem_error("File not found",
                                            std::error_code());
  }

  std::ifstream file(filePath);
  if (!file.is_open()) {
    throw std::ios_base::failure("Could not open file");
  }

  Reports reports;
  std::string line;
  while (std::getline(file, line)) {
    std::vector<int> levels;
    std::istringstream stream(line);
    int number;

    while (stream >> number) {
      levels.push_back(number);
    }

    reports.push_back(levels);
  }

  file.close();

  return reports;
}

int countSafeReports(const Reports &reports, DumpenerMode mode) {
  int count = 0;
  if (mode == DumpenerMode::OFF) {
    for (const auto &report : reports) {
      if (getSafetyViolationIndex(report) == -1) {
        ++count;
      }
    }

    return count;
  }

  for (const auto &report : reports) {
    if (isReportSafeWithDampener(report)) {
      ++count;
    }
  }

  return count;
}

int getSafetyViolationIndex(const Report &report) {
  int index = -1;
  int direction =
      report[0] > report[1] ? Direction::DECREASING : Direction::INCREASING;
  for (int i = 0; i < report.size() - 1; ++i) {
    int nextDirection = report[i] > report[i + 1] ? Direction::DECREASING
                                                  : Direction::INCREASING;
    if (direction != nextDirection) {
      index = i;
      break;
    }

    int diff = std::abs(report[i] - report[i + 1]);
    if (diff < 1 || diff > 3) {
      index = i;
      break;
    }
  }

  return index;
}

bool isReportSafeWithDampener(const Report &report) {
  int safetyViolationIndex = getSafetyViolationIndex(report);
  if (getSafetyViolationIndex(report) == -1) {
    return true;
  }

  for (int i = 0; i < 3; i++) {
    std::vector<int> dumpenedReport;
    int index = safetyViolationIndex + i;
    dumpenedReport.reserve(report.size() - 1);
    dumpenedReport.insert(dumpenedReport.end(), report.begin(),
                          report.begin() + index);
    dumpenedReport.insert(dumpenedReport.end(), report.begin() + index + 1,
                          report.end());

    if (getSafetyViolationIndex(dumpenedReport) == -1) {
      return true;
    }
  }

  return false;
}

} // namespace reports