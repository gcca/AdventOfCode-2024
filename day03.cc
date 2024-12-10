#include <charconv>
#include <numeric>

#include <gtest/gtest.h>

static int ScanAndMul(std::string &corrupted) {
  std::size_t pos = 0;

  std::vector<std::pair<std::string_view, std::string_view>> pairs;
  pairs.reserve(10);

  while ((pos = corrupted.find("mul(", pos)) != std::string::npos) {
    pos = pos + 4;

    char *lhs = &corrupted[pos];

    std::size_t count = pos;
    while (std::isdigit(corrupted[count]))
      count++;

    if (corrupted[count] != ',') {
      pos = count;
      continue;
    }

    std::size_t lhs_len = count - pos;

    pos = ++count;

    char *rhs = &corrupted[count];
    while (std::isdigit(corrupted[count]))
      count++;

    if (corrupted[count] != ')') {
      pos = count;
      continue;
    }

    pairs.emplace_back(std::make_pair(std::string_view(lhs, lhs_len),
                                      std::string_view(rhs, count - pos)));
  }

  return std::transform_reduce(
      pairs.cbegin(), pairs.cend(), 0, std::plus<>(), [](const auto &p) {
        const auto &[larg, rarg] = p;

        int lhs, rhs;
        std::from_chars(larg.data(), larg.data() + larg.size(), lhs);
        std::from_chars(rarg.data(), rarg.data() + rarg.size(), rhs);

        return lhs * rhs;
      });
}

TEST(AdventOfCode2024, Day03) {
  std::string corrupted =
      "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

  EXPECT_EQ(ScanAndMul(corrupted), 161);
}
