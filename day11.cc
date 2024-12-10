#include <gtest/gtest.h>

static std::size_t CountStones(std::vector<std::size_t> stones, int k) {
  while (k-- > 0) {
    std::vector<std::size_t> new_stones;
    new_stones.reserve(2 * stones.size());

    for (auto &s : stones) {
      if (s == 0)
        new_stones.push_back(1);
      else {
        std::size_t ndigits = static_cast<std::size_t>(std::log10(s)) + 1;

        if (!(ndigits % 2)) {
          std::size_t c = ndigits / 2, d = c;
          std::size_t p = s;

          while (c-- > 0)
            p /= 10;

          new_stones.push_back(p);
          new_stones.push_back(s -
                               p * static_cast<std::size_t>(std::pow(10, d)));
        } else
          new_stones.push_back(s * 2024);
      }
    }

    stones = std::move(new_stones);
  }

  return stones.size();
}

TEST(AdventOfCode2024, Day11) {
  EXPECT_EQ(CountStones({0, 1, 10, 99, 999}, 1), 7);
  EXPECT_EQ(CountStones({125, 17}, 6), 22);
  EXPECT_EQ(CountStones({125, 17}, 25), 55312);
}
