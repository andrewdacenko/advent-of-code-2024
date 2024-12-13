#include "blink.hpp"

#include <cmath>
#include <ranges>
#include <vector>

namespace blink {
uint64_t countStones(const std::string &data, size_t times, bool second) {
  std::vector<uint64_t> stones;
  for (const auto &part : std::views::split(data, ' ')) {
    stones.emplace_back(std::stoull(std::string(part.begin(), part.end())));
  }
 
  for (size_t count = 0; count < times; count++) {
    for (int i = 0; i < stones.size(); i++) {
      if (stones[i] == 0)  {
        stones[i] = 1;
        continue;
      }

      if (int(std::log10(stones[i]) + 1) % 2 == 0) {
        auto num = std::to_string(stones[i]);
        stones[i] = std::stoull(num.substr(0, num.size() / 2));
        stones.insert(stones.begin() + i + 1, std::stoull(num.substr(num.size() / 2, num.size())));
        i++;
        continue;
      }

      stones[i] *= 2024;
    }
  }

  return stones.size();
}
}
