#include "updates.hpp"

#include <functional>
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

std::optional<InvalidRecord> getInvalidRecord(const Rules &rules,
                                              const Update &update) {
  for (int i = 0; i < update.size(); i++) {
    auto rule = rules.at(update[i]);
    for (int j = 0; j < update.size(); j++) {

      if (j < i) {
        if (!rules.at(update[j]).contains(update[i])) {
          return std::pair<int, int>(j, i);
        };
      }

      if (i < j) {
        if (!rule.contains(update[j])) {
          return std::pair<int, int>(i, j);
        }
      }
    }
  }

  return std::nullopt;
};

int countValidUpdates(const Rules &rules, const Updates &updates) {
  int sum = 0;

  for (auto &update : updates) {
    if (!getInvalidRecord(rules, update).has_value()) {
      sum += update[update.size() / 2];
    }
  }

  return sum;
}

int countInvalidUpdates(const Rules &rules, const Updates &updates) {
  int sum = 0;

  std::function<Update(const InvalidRecord &, const Update &)> findValidUpdate;
  findValidUpdate = [&rules, &findValidUpdate](const InvalidRecord &record,
                                               const Update &update) -> Update {
    auto [i, j] = record;

    Update newUpdate = {update.begin(), update.begin() + i};
    newUpdate.push_back(update[j]);
    newUpdate.append_range(Update{update.begin() + i, update.begin() + j});
    newUpdate.append_range(Update{update.begin() + j + 1, update.end()});

    auto res = getInvalidRecord(rules, newUpdate);
    if (res.has_value()) {
      return findValidUpdate(res.value(), newUpdate);
    }

    return newUpdate;
  };

  for (auto &update : updates) {
    auto invalidRecord = getInvalidRecord(rules, update);
    if (invalidRecord.has_value()) {
      auto res = findValidUpdate(invalidRecord.value(), update);
      sum += res[res.size() / 2];
    }
  }

  return sum;
}
} // namespace updates