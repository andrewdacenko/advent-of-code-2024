#include "safety.hpp"

#include <optional>
#include <print>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace safety {
struct Robot {
  int x;
  int y;
  int vx;
  int vy;
};

struct Hasher {
  size_t operator()(const std::pair<int, int> &p) const {
    return std::hash<int>{}(p.first) ^ std::hash<int>{}(p.second);
  }
};

int christmasTree(const std::vector<Robot> &robots) {
  int spaceX = 101;
  int spaceY = 103;
  int midX = spaceX / 2;
  int midY = spaceY / 2;

  auto uniquePositions = [&](int seconds)
      -> std::optional<std::unordered_set<std::pair<int, int>, Hasher>> {
    auto teleport = [&](const Robot robot) -> std::pair<int, int> {
      auto nextX = (robot.x + seconds * robot.vx) % spaceX;
      auto nextY = (robot.y + seconds * robot.vy) % spaceY;

      if (nextX < 0) {
        nextX = spaceX + nextX;
      }
      if (nextY < 0) {
        nextY = spaceY + nextY;
      }

      return {nextX, nextY};
    };

    std::unordered_set<std::pair<int, int>, Hasher> res;
    for (auto v : robots) {
      res.insert(teleport(v));
    }

    if (res.size() == robots.size()) {
      return res;
    }

    return std::nullopt;
  };

  for (int i = 0; i <= 10000; i++) {
    if (auto v = uniquePositions(i); v.has_value()) {
      auto res = v.value();
      std::string data;
      for (int i = 0; i < spaceY; i++) {
        for (int j = 0; j < spaceX; j++) {
          if (res.contains({j, i})) {
            data += '1';
          } else {
            data += '.';
          }
        }
        data += '\n';
      }

      std::print("{}", data);
      return i;
    }
  }

  return -1;
}

int countScore(const std::vector<std::string> &grid, bool second) {
  int seconds = 100;
  int spaceX = 101;
  int spaceY = 103;
  int midX = spaceX / 2;
  int midY = spaceY / 2;

  std::vector<Robot> robots;
  for (auto const &line : grid) {
    Robot robot;
    char discard;
    std::istringstream lineStream(line);
    lineStream >> discard >> discard >> robot.x >> discard >> robot.y >>
        discard >> discard >> robot.vx >> discard >> robot.vy;
    robots.push_back(robot);
  }

  if (second) {
    return christmasTree(robots);
  }

  auto teleport = [&](const Robot robot) -> int {
    auto nextX = (robot.x + seconds * robot.vx) % spaceX;
    auto nextY = (robot.y + seconds * robot.vy) % spaceY;

    if (nextX < 0) {
      nextX = spaceX + nextX;
    }
    if (nextY < 0) {
      nextY = spaceY + nextY;
    }

    if (nextX < midX && nextY < midY)
      return 0;
    if (nextX < midX && nextY > midY)
      return 1;
    if (nextX > midX && nextY > midY)
      return 2;
    if (nextX > midX && nextY < midY)
      return 3;
    return 4;
  };

  std::vector<int> positions{0, 0, 0, 0, 0};
  for (const auto &robot : robots) {
    positions[teleport(robot)]++;
  }

  return positions[0] * positions[1] * positions[2] * positions[3];
}
} // namespace safety
