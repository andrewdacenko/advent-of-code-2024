#pragma once

#include <__format/format_functions.h>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace warehouse {

class Pos {
public:
  struct Hash {
    size_t operator()(const Pos &pos) const {
      return std::hash<int>{}(pos.row) ^ std::hash<int>{}(pos.col);
    }
  };

  int row;
  int col;
  int width{1};

  bool operator==(const Pos &p) const { return row == p.row && col == p.col; }
};

class Warehouse {
public:
  Warehouse(const std::vector<std::string> &grid, bool second);
  ~Warehouse() = default;

  int countGPS();

private:
  static inline bool debug = false;
  const static inline std::unordered_map<char, std::tuple<int, int>> dirs{
      {'^', {-1, 0}}, {'v', {1, 0}}, {'<', {0, -1}}, {'>', {0, 1}}};

  int scale;
  int rows_, cols_ = 0;
  std::string moves_;
  Pos robot_;
  std::unordered_set<Pos, Pos::Hash> boxes_;
  std::unordered_set<Pos, Pos::Hash> walls_;

  bool canMove(const Pos &pos, char move) const;
  void printWarehouse() const;
  std::vector<Pos> getHorizontalBoxes(const Pos &pos, char dir);

  template <class... _Args>
  void print(std::format_string<_Args...> __fmt, _Args &&...__args) const;
};

} // namespace warehouse
