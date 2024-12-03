#pragma once

#include <vector>

namespace mult {

using Instructions = std::vector<int>;

Instructions parseInstructions(const std::string& filePath);
int calculate(const Instructions& instructions);

} // namespace mult
