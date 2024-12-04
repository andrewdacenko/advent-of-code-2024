#include "Mult.hpp"
#include <string>
#include <unistd.h>

struct Config {
  std::string inputFile;
  mult::MultMode mode{mult::MultMode::MULT_IT_OVER};
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
    switch (getopt(argc, argv, "hdi:")) {
    case 'i':
      config.inputFile = optarg;
      continue;
    case 'd':
      config.mode = mult::MultMode::ON_OFF;
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

  auto result =
      mult::calculate(mult::parseInstructions(config.inputFile, config.mode));
  printf("Mult: %d\n", result);

  return 0;
}