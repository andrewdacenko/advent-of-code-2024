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
  locations::LocationsLists locations;
};

void printHelp(const char *progname) {
  fprintf(stderr, "Usage: [OPTION]...\n"
                  "Example: -h\n"
                  "\n"
                  "  -i        Input file path\n"
                  "  -h        Print out this help\n"
                  "\n");
}

int main(int argc, char **argv) {
  Config config;
  for (;;) {
    switch (getopt(argc, argv, "hsi:")) {
    case 'i':
      config.locations = locations::getLocations(optarg);
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

  auto result = config.lookup == Lookup::Diff
                    ? locations::compareLocations(config.locations)
                    : locations::computeSimilarity(config.locations);

  printf("%s: %d\n",
         config.lookup == Lookup::Diff ? "Differences" : "Similarity", result);

  return 0;
}