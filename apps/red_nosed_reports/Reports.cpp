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

const int countSafeReports(const Reports &reports) {
  int count = 0;
  for (const auto &report : reports) {
    int safe = true;
    int direction =
        report[0] > report[1] ? Direction::DECREASING : Direction::INCREASING;
    for (int i = 0; i < report.size() - 1; ++i) {
      int nextDirection = report[i] > report[i + 1] ? Direction::DECREASING
                                                    : Direction::INCREASING;
      if (direction != nextDirection) {
        safe = false;
        break;
      }

      int diff = std::abs(report[i] - report[i + 1]);
      if (diff < 1 || diff > 3) {
        safe = false;
        break;
      }
    }

    if (safe) {
      ++count;
    }
  }

  return count;
}

} // namespace reports