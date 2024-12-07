#include "program_options.hpp"
#include <cstdio>
#include <iostream>
#include <unistd.h>

namespace {

void printHelp() {
  fprintf(stderr, "Usage: [OPTION]...\n"
                  "Example: -h\n"
                  "\n"
                  "  -i        Input file path (Required)\n"
                  "  -s        Run second part\n"
                  "  -h        Print out this help\n"
                  "\n");
}

} // namespace

namespace program_options {

int parse(int argc, char *argv[], Options& options) {
  for (;;) {
    switch (getopt(argc, argv, "hsi:")) {
    case 'i':
      options.inputFileName = optarg;
      continue;
    case 's':
      options.second = true;
      continue;

    case '?':
    case 'h':
    default:
      printHelp();
      return -1;

    case -1:
      break;
    }

    break;
  }

  if (options.inputFileName.empty()) {
    fprintf(stderr, "Missing required input file path.\n");
    printHelp();
    return -1;
  }

  return 0;
};

} // namespace program_options
