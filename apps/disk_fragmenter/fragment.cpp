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
  if (second) {
    return checksumFiles(data);
  }

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

Num checksumFiles(const std::string &data) {
  std::vector<File> disk;
  int addr = 0;
  for (int i = 0; i < data.size(); i += 2) {
    int size = data[i] - '0';
    int empty = i + 1 < data.size() ? data[i + 1] - '0' : 0;
    disk.push_back({addr, Num(i / 2), size, empty});
    addr += size + empty;
  }

  auto calc = [](int addr, Num id, int n) {
    Num sum = 0;
    for (int i = 0; i < n; i++) {
      sum += (addr + i) * id;
    }
    return sum;
  };

  Num checksum = 0;
  for (auto start = disk.begin(), end = disk.end() - 1; end != start;) {
    auto destination = start;
    auto file = end;
    for (;;) {
      if (destination >= file - 1) {
        break;
      }

      if (destination->empty >= file->size) {
        break;
      }

      destination++;
    }

    if (destination == file || destination->empty < file->size) {
      checksum += calc(file->addr, file->id, file->size);
      end--;
      continue;
    }

    destination->empty -= file->size;
    auto fileChecksum =
        calc(destination->addr + destination->size + destination->filled,
             file->id, file->size);
    destination->filled += file->size;
    checksum += fileChecksum;
    end--;
  }

  return checksum;
}
} // namespace fragment