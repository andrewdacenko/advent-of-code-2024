#include "fragment.hpp"
#include <cstdio>
#include <vector>

namespace fragment {
void prettyPrint(const std::vector<Block> &blocks) {
  for (auto block : blocks) {
    printf("%s", block.allocated ? std::to_string(block.id).c_str() : ".");
  }
  printf("\n");
}

Num checksum(const std::string &data, bool second) {
  std::vector<Block> buffer;
  for (int i = 0; i < data.size(); i++) {
    int num = data[i] - '0';
    for (int j = 0; j < num; j++) {
      buffer.push_back({Num(i / 2), i % 2 == 0});
    }
  }

  Num chechsum = 0;
  for (int i = 0, j = buffer.size(); i != j + 1;) {
    if (buffer[i].allocated) {
      chechsum += i * buffer[i].id;
      i++;
      continue;
    } else if (buffer[j].allocated) {
      std::swap(buffer[i], buffer[j]);
    }

    j--;
  }

  return chechsum;
}
} // namespace fragment