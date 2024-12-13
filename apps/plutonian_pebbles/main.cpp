#include "blink.hpp"

#include <files/files.hpp>
#include <print>
#include <program_options/program_options.hpp>

int main(int argc, char **argv) {
  program_options::Options options;
  if (auto code = program_options::parse(argc, argv, options); code != 0) {
    return code;
  }

  auto data = files::getContent(options.inputFileName);
  auto res = blink::countStones(data, 25, options.second);
  std::println("Stones: {}", res);

  return 0;
}
