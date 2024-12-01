#include "Locations.hpp"

#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

struct Config {
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
    switch (getopt(argc, argv, "hi:")) {
    case 'i':
      config.locations = locations::getLocations(optarg);
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

  auto diff = locations::compareLocations(config.locations);

  printf("Differences: %d\n", diff);

  return 0;
}