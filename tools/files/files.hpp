#include <string>
#include <vector>

namespace files {
std::string getContent(const std::string& filename);
std::vector<std::string> getLines(const std::string& filename);
} // namespace files
