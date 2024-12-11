#include <string>

namespace fragment {
using Num = unsigned long;
struct Block {
  Num id;
  bool allocated;
};
Num checksum(const std::string &data, bool second);
} // namespace fragment