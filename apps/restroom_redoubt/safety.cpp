#include "safety.hpp"

#include <sstream>
#include <vector>

namespace safety {
struct Robot {
  int x;
  int y;
  int vx;
  int vy;
};

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
