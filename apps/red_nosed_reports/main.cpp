#include "Reports.hpp"

#include <cstdio>
#include <unistd.h>

using namespace reports;

struct Config {
  DumpenerMode mode;
  std::string inputFile;
};

void printHelp(const char *progname) {
  fprintf(stderr, "Usage: [OPTION]...\n"
                  "Example: -h\n"
                  "\n"
                  "  -i        Input file path. Required\n"
                  "  -h        Print out this help\n"
                  "\n");
}

int main(int argc, char **argv) {
  Config config;
  for (;;) {
    switch (getopt(argc, argv, "hdi:")) {
    case 'i':
      config.inputFile = optarg;
      continue;
    case 'd':
      config.mode = DumpenerMode::ON;
      continue;

    case '?':
    case 'h':
    default:
      printHelp(argv[0]);
      return -1;

    case -1:
      break;
    }

    break;
  }

  if (config.inputFile.empty()) {
    printf("Missing mandatory input file\n");
    printHelp(argv[0]);
    return -1;
  }

  const auto result =
      countSafeReports(getReports(config.inputFile), config.mode);
  printf("Number of safe reports: %d\n", result);
  return 0;
}