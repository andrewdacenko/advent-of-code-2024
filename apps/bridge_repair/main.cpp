#include "calibration.hpp"

#include <cstdio>
#include <files/files.hpp>
#include <program_options/program_options.hpp>
#include <string>

int main(int argc, char **argv) {
  program_options::Options options;
  if (auto code = program_options::parse(argc, argv, options); code != 0) {
    return code;
  }

  auto data = files::getLines(options.inputFileName);
  auto res = calibration::countCalibrations(data, options.second);
  printf("Sum: %llu\n", res);

  return 0;
}