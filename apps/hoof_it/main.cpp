#include "trail.hpp"

#include <files/files.hpp>
#include <print>
#include <program_options/program_options.hpp>

int main(int argc, char **argv) {
  program_options::Options options;
  if (auto code = program_options::parse(argc, argv, options); code != 0) {
    return code;
  }

  auto data = files::getLines(options.inputFileName);
  auto res = trail::countTrails(data, options.second);
  std::println("Trails: {}", res);

  return 0;
}