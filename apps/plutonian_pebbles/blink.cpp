#include "blink.hpp"

#include <cmath>
#include <ranges>
#include <unordered_map>
#include <vector>

namespace blink {
struct Hasher {
  std::size_t operator()(const std::pair<uint64_t, size_t> &v) const {
    std::size_t h1 = std::hash<int>{}(v.first);
    std::size_t h2 = std::hash<int>{}(v.second);
    return h1 ^ (h2 << 1); // XOR and shift to combine hashes
  }
};

std::unordered_map<std::pair<uint64_t, size_t>, uint64_t, Hasher> cache;

uint64_t count(uint64_t n, size_t times) {
  auto key = std::make_pair(n, times);
  if (cache.contains(key)) {
    return cache[key];
  }

  if (times == 0) {
    return 1;
  }

  if (n == 0) {
    cache[key] = count(1, times - 1);
  } else if (int(std::log10(n) + 1) % 2 == 0) {
    std::string s = std::to_string(n);
    cache[key] = count(std::stoull(s.substr(0, s.size() / 2)), times - 1) +
                 count(std::stoull(s.substr(s.size() / 2)), times - 1);
  } else {
    cache[key] = count(n * 2024, times - 1);
  }

  return cache[key];
}

uint64_t countStones(const std::string &data, bool second) {
  size_t times = second ? 75 : 25;
  std::vector<uint64_t> stones;
  for (const auto &part : std::views::split(data, ' ')) {
    stones.emplace_back(std::stoull(std::string(part.begin(), part.end())));
  }

  uint64_t res = 0;
  for (int i = 0; i < stones.size(); i++) {
    res += count(stones[i], times);
  }

  return res;
}
} // namespace blink
