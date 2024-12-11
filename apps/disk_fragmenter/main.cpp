#include "fragment.hpp"

#include <cstdio>
#include <files/files.hpp>
#include <program_options/program_options.hpp>
#include <string>

int main(int argc, char **argv) {
  program_options::Options options;
  if (auto code = program_options::parse(argc, argv, options); code != 0) {
    return code;
  }

  auto data = files::getContent(options.inputFileName);
  auto res = fragment::checksum(data, options.second);
  printf("Checksum: %s\n", std::to_string(res).c_str());

  return 0;
}