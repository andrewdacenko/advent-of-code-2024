#include "arcade.hpp"

#include <algorithm>
#include <numeric>
#include <print>
#include <ranges>
#include <sstream>

namespace arcade {
struct Button {
  uint64_t x;
  uint64_t y;
};

struct Prize {
  uint64_t x;
  uint64_t y;
};

struct Game {
  Button buttonA;
  Button buttonB;
  Prize prize;

  uint64_t tokensToWin() const {
    uint64_t tokens = 400; // 100 * A (3 tokens each) + 100 * B (1 token each)
    uint64_t maxA = std::min((uint64_t)std::ceil(prize.x / buttonA.x),
                             (uint64_t)std::ceil(prize.y / buttonA.y));
    uint64_t maxB = std::min((uint64_t)std::ceil(prize.x / buttonB.x),
                             (uint64_t)std::ceil(prize.y / buttonB.y));

    for (uint64_t i = 0; i <= maxA; i++) {
      for (uint64_t j = 0; j <= maxB; j++) {
        if (i * buttonA.x + j * buttonB.x == prize.x &&
            i * buttonA.y + j * buttonB.y == prize.y) {
          if ((i * 3 + j) < tokens) {
            tokens = i * 3 + j;
          }
        }
      }
    }

    return tokens == 400 ? 0 : tokens;
  }
};

uint64_t countTokens(const std::vector<std::string> &lines, bool second) {
  std::vector<Game> games;
  Game game;
  for (auto line : lines) {
    if (line.empty()) {
      continue;
    }
    if (line.contains("Button A: ")) {
      game.buttonA.x = std::stoi(line.substr(12, 2));
      game.buttonA.y = std::stoi(line.substr(18, 2));
    }
    if (line.contains("Button B: ")) {
      game.buttonB.x = std::stoi(line.substr(12, 2));
      game.buttonB.y = std::stoi(line.substr(18, 2));
    }
    if (line.contains("Prize: ")) {
      game.prize.x = std::stoi(line.substr(
          line.find("X=") + 2, line.find(",") - line.find("X=") + 2));
      game.prize.y = std::stoi(
          line.substr(line.find("Y=") + 2, line.size() - line.find("Y=") + 2));
      games.push_back(game);
      game = Game();
    }
  }

  return std::accumulate(
      games.begin(), games.end(), 0,
      [](auto acc, const Game &game) { return acc + game.tokensToWin(); });
}
} // namespace arcade
