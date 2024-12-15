#include "arcade.hpp"

#include <algorithm>
#include <numeric>
#include <print>
#include <ranges>
#include <sstream>

namespace arcade {
struct Button {
  int64_t x;
  int64_t y;
};

struct Prize {
  int64_t x;
  int64_t y;
};

struct Game {
  Button buttonA;
  Button buttonB;
  Prize prize;

  int64_t tokensToWin() const {
    // AX * pa + BX * pb = PX
    // AY * pa + BY * pb = PY
    // pa = (PX - BX * pb) / AX
    // AY * (PX - BX * pb) + AX * BY * pb = AX * PY
    // AY * PX - AY * BX * pb + AX * BY * pb = AX * PY
    // pb (AX * BY - AY * BX) = AX * PY - AY * PX
    // pb = (AX * PY - AY * PX) / (AX * BY - AY * BX)
    auto pressB = (buttonA.x * prize.y - buttonA.y * prize.x) /
                  (buttonA.x * buttonB.y - buttonA.y * buttonB.x);
    // pa = (PX - pb * BX) / AX
    auto pressA = (prize.x - buttonB.x * pressB) / buttonA.x;

    if (pressA < 0 || pressB < 0)
      return 0;
    if (pressA * buttonA.x + pressB * buttonB.x != prize.x)
      return 0;
    if (pressA * buttonA.y + pressB * buttonB.y != prize.y)
      return 0;

    return pressA * 3 + pressB;
  }
};

int64_t countTokens(const std::vector<std::string> &lines, bool second) {
  int64_t extra = second ? 10000000000000ll : 0ll;
  std::vector<Game> games;
  Game game;
  for (auto line : lines) {
    if (line.empty()) {
      continue;
    }
    if (line.contains("Button A: ")) {
      game.buttonA.x = std::stoll(line.substr(12, 2));
      game.buttonA.y = std::stoll(line.substr(18, 2));
    }
    if (line.contains("Button B: ")) {
      game.buttonB.x = std::stoll(line.substr(12, 2));
      game.buttonB.y = std::stoll(line.substr(18, 2));
    }
    if (line.contains("Prize: ")) {
      game.prize.x =
          std::stoll(line.substr(line.find("X=") + 2,
                                 line.find(",") - line.find("X=") + 2)) +
          extra;
      game.prize.y =
          std::stoll(line.substr(line.find("Y=") + 2,
                                 line.size() - line.find("Y=") + 2)) +
          extra;
      games.push_back(game);
      game = Game();
    }
  }

  return std::accumulate(
      games.begin(), games.end(), 0ll,
      [](auto acc, const Game &game) { return acc + game.tokensToWin(); });
}
} // namespace arcade
