#pragma once

#include <vector>

namespace mult {

enum MultMode {
  ON_OFF,
  MULT_IT_OVER
};


using Instructions = std::vector<int>;

Instructions parseInstructions(const std::string& filePath, MultMode mode);
int calculate(const Instructions& instructions);

} // namespace mult
