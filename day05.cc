#include <gtest/gtest.h>

static std::pair<std::vector<bool>, int>
CheckCorrectness(const std::vector<std::string> &rules,
                 const std::vector<std::string> &update) {
  std::vector<std::pair<int, int>> rule_pairs;

  for (const auto &rule : rules) {
    auto pos = rule.find('|');
    rule_pairs.push_back(
        {std::stoi(rule.substr(0, pos)), std::stoi(rule.substr(pos + 1))});
  }

  std::vector<std::vector<int>> update_values;

  for (const auto &u : update) {
    std::vector<int> values;

    std::size_t start = 0, pos = u.find(',');

    while (pos != std::string::npos) {
      values.push_back(std::stoi(u.substr(start, pos)));

      start = pos + 1;
      pos = u.find(',', start);
    }
    values.push_back(std::stoi(u.substr(start, pos)));

    update_values.push_back(values);
  }

  std::unordered_map<int, std::vector<int>> cache;

  for (const auto &val : rule_pairs) {
    cache[val.second].push_back(val.first);
  }

  int count = 0;
  std::vector<bool> results;
  results.reserve(update_values.size());

  std::transform(
      update_values.begin(), update_values.end(), std::back_inserter(results),
      [&cache, &count](const auto &up) mutable {
        for (std::size_t i = 0; i < up.size() - 1; ++i) {
          const auto &refs = cache[up[i]];

          for (std::size_t j = i + 1; j < up.size(); ++j) {
            if (std::find(refs.begin(), refs.end(), up[j]) != refs.end())
              return false;
          }
        }

        count += up[up.size() / 2];

        return true;
      });

  return std::make_pair(std::move(results), count);
}

TEST(AdventOfCode2024, Day05) {
  std::vector<std::string> rules{
      "47|53", "97|13", "97|61", "97|47", "75|29", "61|13", "75|53",
      "29|13", "97|29", "53|29", "61|53", "97|53", "61|29", "47|13",
      "75|47", "97|75", "47|61", "75|61", "47|29", "75|13", "53|13"};

  std::vector<std::string> updates{"75,47,61,53,29", "97,61,53,29,13",
                                   "75,29,13",       "75,97,47,61,53",
                                   "61,13,29",       "97,13,75,29,47"};

  EXPECT_EQ(CheckCorrectness(rules, updates),
            (std::make_pair<std::vector<bool>, int>(
                {true, true, true, false, false, false}, 143)));
}
