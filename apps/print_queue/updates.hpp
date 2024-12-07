#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <string>

namespace updates {

using Rules = std::unordered_map<int, std::unordered_set<int>>;
using Update = std::vector<int>;
using Updates = std::vector<Update>;

std::pair<Rules, Updates> parseRulesAndUpdates(const std::vector<std::string>& lines);
int countValidUpdates(const Rules &rules, const Updates &updates);

} // namespace updates