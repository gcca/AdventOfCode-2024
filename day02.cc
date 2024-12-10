#include <numeric>
#include <vector>

#include <gtest/gtest.h>

static int IsSafe(std::vector<int> report) {
  std::vector<int> diffs;
  diffs.reserve(report.size());

  std::adjacent_difference(report.cbegin(), report.cend(),
                           std::back_inserter(diffs));

  int dist = std::abs(diffs[1]);

  if ((dist < 1) || (dist > 3))
    return 0;

  int prev_sign = diffs[1] > 0 ? 1 : diffs[1] < 0 ? -1 : 0;

  for (std::size_t i = 2; i < diffs.size(); ++i) {
    int diff = diffs[i];

    dist = std::abs(diff);

    if ((dist < 1) || (dist > 3))
      return 0;

    int curr_sign = diff > 0 ? 1 : diff < 0 ? -1 : 0;

    if (prev_sign * curr_sign < 0)
      return 0;
  }

  return 1;
}

static int CountSafe(std::vector<std::vector<int>> levels) {
  return std::transform_reduce(levels.cbegin(), levels.cend(), 0,
                               std::plus<int>(), IsSafe);
}

TEST(AdventOfCode2024, Day02) {
  std::vector<std::vector<int>> levels{{7, 6, 4, 2, 1}, {1, 2, 7, 8, 9},
                                       {9, 7, 6, 2, 1}, {1, 3, 2, 4, 5},
                                       {8, 6, 4, 4, 1}, {1, 3, 6, 7, 9}};

  EXPECT_EQ(CountSafe(levels), 2);
}
