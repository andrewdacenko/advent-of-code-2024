#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace updates {

using Rules = std::unordered_map<int, std::unordered_set<int>>;
using InvalidRecord = std::pair<int, int>;
using Update = std::vector<int>;
using Updates = std::vector<Update>;

std::pair<Rules, Updates>
parseRulesAndUpdates(const std::vector<std::string> &lines);
std::optional<InvalidRecord> getInvalidRecord(const Rules &rules,
                                              const Update &update);
int countValidUpdates(const Rules &rules, const Updates &updates);
int countInvalidUpdates(const Rules &rules, const Updates &updates);

} // namespace updates