#include "updates.hpp"

#include <cstdio>
#include <files/files.hpp>
#include <program_options/program_options.hpp>

int main(int argc, char **argv) {
  program_options::Options options;
  if (auto code = program_options::parse(argc, argv, options); code != 0) {
    return code;
  }

  auto res = updates::parseRulesAndUpdates(files::getLines(options.inputFileName));
  printf("Sum: %d\n", updates::countValidUpdates(res.first, res.second));

  return 0;
}