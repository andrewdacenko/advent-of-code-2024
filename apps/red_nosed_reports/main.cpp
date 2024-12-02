#include "Reports.hpp"

#include <cstdio>
#include <unistd.h>

struct Config {
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
    switch (getopt(argc, argv, "hi:")) {
    case 'i':
      config.inputFile = optarg;
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
      reports::countSafeReports(reports::getReports(config.inputFile));
  printf("Number of safe reports: %d\n", result);
  return 0;
}