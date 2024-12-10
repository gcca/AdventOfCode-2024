#include <gtest/gtest.h>

static std::size_t ComputeTokens(std::pair<std::size_t, std::size_t> a,
                                 std::pair<std::size_t, std::size_t> b,
                                 std::pair<std::size_t, std::size_t> c) {
  if (a.first * b.second == a.second * b.first)
    return 0;

  std::size_t x = (c.first * b.second - c.second * b.first) /
                  (a.first * b.second - a.second * b.first);

  std::size_t y = (a.first * c.second - a.second * c.first) /
                  (a.first * b.second - a.second * b.first);

  if (x == 0 and y == 0)
    for (; x <= 100; x++) {
      y = (c.first / b.first) - (a.first * x / b.first);

      if (a.first * x + b.first * y == c.first and
          a.second * x + b.second * y == c.second)
        return 3 * x + y;
    }

  if (x > 100 or y > 100)
    return 0;

  return 3 * x + y;
}

TEST(AdeventOfCode2024, Day13) {
  EXPECT_EQ(ComputeTokens({94, 34}, {22, 67}, {8400, 5400}), 280);
  EXPECT_EQ(ComputeTokens({26, 66}, {67, 21}, {12748, 12176}), 0);
  EXPECT_EQ(ComputeTokens({17, 86}, {84, 37}, {7870, 6450}), 200);
  EXPECT_EQ(ComputeTokens({69, 23}, {27, 71}, {18641, 10279}), 0);
}
