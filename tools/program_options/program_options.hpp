#include <memory>
#include <string>

namespace program_options {
struct Options {
  std::string inputFileName;
  bool second{false};
};

int parse(int argc, char* argv[], Options& options);

} // namespace program_options