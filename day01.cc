#include <numeric>

#include <gtest/gtest.h>

static int TotalDistance(std::vector<int> &left, std::vector<int> &right) {
  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  return std::transform_reduce(left.cbegin(), left.cend(), right.cbegin(), 0,
                               std::plus<>(),
                               [](int l, int r) { return std::abs(l - r); });
}

TEST(AdventOfCode2024, Day01) {
  std::vector<int> left{3, 4, 2, 1, 3, 3}, right{4, 3, 5, 3, 9, 3};

  EXPECT_EQ(TotalDistance(left, right), 11);
}
