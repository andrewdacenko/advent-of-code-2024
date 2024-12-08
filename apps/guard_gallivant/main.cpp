#include "path.hpp"

#include <cstdio>
#include <files/files.hpp>
#include <program_options/program_options.hpp>

int main(int argc, char **argv) {
  program_options::Options options;
  if (auto code = program_options::parse(argc, argv, options); code != 0) {
    return code;
  }

  auto grid = files::getLines(options.inputFileName);
  auto res = options.second ? path::countLoops(grid) : path::countMoves(grid);
  printf("Sum: %d\n", res);

  return 0;
}