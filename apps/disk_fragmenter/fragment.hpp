#include <string>
#include <utility>
#include <vector>

namespace fragment {
using Num = unsigned long;
struct Block {
  Num id;
  bool allocated;
};
struct File {
  int addr;
  Num id;
  int size;
  int empty;
  int filled;
};
Num checksum(const std::string &data, bool second);
Num checksumFiles(const std::string &data);
} // namespace fragment