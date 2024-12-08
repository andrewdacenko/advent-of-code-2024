#include "calibration.hpp"

#include <exception>
#include <ranges>

namespace calibration {
std::vector<Num> split(const std::string &input, char delimiter) {
  std::vector<Num> result;
  for (const auto &part : std::views::split(input, delimiter)) {
    result.emplace_back(std::stoull(std::string(part.begin(), part.end())));
  }
  return result;
}

Num calibrate(const std::string &instruction, bool concatEnabled) {
  int col = instruction.find(':');
  Num total = std::stoull(instruction.substr(0, col));
  std::vector<Num> nums = split(instruction.substr(col + 2), ' ');
  return Operation{nums[0],
                   total,
                   {nums.begin() + 1, nums.end()},
                   std::to_string(nums[0]),
                   concatEnabled}
      .calibrate();
}

Num countCalibrations(const std::vector<std::string> &data,
                      bool concatEnabled) {
  Num sum = 0;
  for (const auto &line : data) {
    sum += calibrate(line, concatEnabled);
  }
  return sum;
}
} // namespace calibration