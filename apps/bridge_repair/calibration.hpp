#pragma once

#include <string>
#include <vector>

namespace calibration {
using Num = unsigned long long;

struct Operation {
  Num num;
  Num expect;
  std::vector<Num> rest;
  std::string debug;

  Num calibrate() {
    if (num > expect) {
      return 0;
    }

    if (rest.size() == 0) {
      return expect == num ? expect : 0;
    }

    auto add = Operation{num + rest[0],
                         expect,
                         {rest.begin() + 1, rest.end()},
                         "(" + debug + " + " + std::to_string(rest[0]) + ")"};
    auto mul = Operation{num * rest[0],
                         expect,
                         {rest.begin() + 1, rest.end()},
                         "(" + debug + " * " + std::to_string(rest[0]) + ")"};

    if (add.calibrate()) {
      return add.expect;
    }

    if (mul.calibrate()) {
      return mul.expect;
    }

    return 0;
  }
};
Num calibrate(const std::string &instruction);
Num countCalibrations(const std::vector<std::string> &data);
} // namespace calibration