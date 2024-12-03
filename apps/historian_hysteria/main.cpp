#include "Locations.hpp"

#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

enum Lookup {
  Diff,
  Similarity,
};

struct Config {
  Lookup lookup{Lookup::Diff};
  std::string inputFile;
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
    switch (getopt(argc, argv, "hsi:")) {
    case 'i':
      config.inputFile = optarg;
      continue;

    case 's':
      config.lookup = Lookup::Similarity;
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

  auto locations = locations::getLocations(config.inputFile);
  auto result = config.lookup == Lookup::Diff
                    ? locations::compareLocations(locations)
                    : locations::computeSimilarity(locations);

  printf("%s: %d\n",
         config.lookup == Lookup::Diff ? "Differences" : "Similarity", result);

  return 0;
}