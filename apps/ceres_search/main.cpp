#include "search.hpp"
#include <string>
#include <unistd.h>

struct Config {
  std::string inputFile;
  bool x{false};
};

void printHelp(const char *progname) {
  fprintf(stderr, "Usage: [OPTION]...\n"
                  "Example: -h\n"
                  "\n"
                  "  -i        Input file path [Required]\n"
                  "  -h        Print out this help\n"
                  "\n");
}

int main(int argc, char **argv) {
  Config config;
  for (;;) {
    switch (getopt(argc, argv, "hxi:")) {
    case 'i':
      config.inputFile = optarg;
      continue;
    case 'x':
      config.x = true;
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
    printf("Missing required input file path.\n");
    printHelp(argv[0]);
    return -1;
  }

  auto lines = search::readFileLines(config.inputFile);
  auto result =
      config.x ? search::countCrossWords(lines) : search::countWords(lines);
  printf("X%sMAS count: %d\n", config.x ? "-" : "", result);

  return 0;
}