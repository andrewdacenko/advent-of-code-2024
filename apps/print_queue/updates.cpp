#include "updates.hpp"

#include <ranges>

namespace {
std::vector<int> split(const std::string &input, char delimiter) {
  std::vector<int> result;
  for (const auto &part : std::views::split(input, delimiter)) {
    result.emplace_back(std::stoi(std::string(part.begin(), part.end())));
  }
  return result;
}
} // namespace

namespace updates {

std::pair<Rules, Updates>
parseRulesAndUpdates(const std::vector<std::string> &lines) {
  Rules rules;
  Updates updates;

  for (auto line : lines) {
    if (line.size() == 5) {
      auto nums = split(line, '|');
      if (!rules.contains(nums[0])) {
        rules[nums[0]] = {};
      }
      if (!rules.contains(nums[1])) {
        rules[nums[1]] = {};
      }

      rules[nums[0]].insert(nums[1]);
    } else {
      updates.push_back(split(line, ','));
    }
  }

  return {rules, updates};
}

int countValidUpdates(const Rules &rules, const Updates &updates) {
  int sum = 0;

  auto isValidUpdate = [&rules](const Update &update) -> bool {
    for (int i = 0; i < update.size(); i++) {
      auto rule = rules.at(update[i]);
      for (int j = 0; j < update.size(); j++) {

        if (j < i) {
          if (!rules.at(update[j]).contains(update[i])) {
            return false;
          };
        }

        if (i < j) {
          if (!rule.contains(update[j])) {
            return false;
          }
        }
      }
    }
    return true;
  };

  for (auto &update : updates) {
    if (isValidUpdate(update)) {
      sum += update[update.size() / 2];
    }
  }

  return sum;
}

} // namespace updates