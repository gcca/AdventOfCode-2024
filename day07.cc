#include <gtest/gtest.h>

template <class BOp>
static bool Calc(int tv, int ax, std::queue<int> q, BOp op) {
  if (q.empty())
    return tv == ax;

  ax = op(ax, q.front());

  q.pop();

  return Calc(tv, ax, q, std::plus<>()) or Calc(tv, ax, q, std::multiplies<>());
}

static int CountCalibrations(
    const std::vector<std::pair<int, std::vector<int>>> &calibrations) {

  int count = 0;

  for (const auto &calibration : calibrations) {
    const auto &tv = calibration.first;
    const auto &os = calibration.second;

    if (Calc(tv, os[0], {os.begin() + 1, os.end()}, std::plus<>()) or
        Calc(tv, os[0], {os.begin() + 1, os.end()}, std::multiplies<>()))
      count += tv;
  }

  return count;
}

TEST(AdventOfCode2024, Day07) {

  std::vector<std::pair<int, std::vector<int>>> calibrations = {
      {190, {10, 19}},    {3267, {81, 40, 27}},    {83, {17, 5}},
      {156, {15, 6}},     {7290, {6, 8, 6, 15}},   {161011, {16, 10, 13}},
      {192, {17, 8, 14}}, {21037, {9, 7, 18, 13}}, {292, {11, 6, 16, 20}},

  };

  EXPECT_EQ(CountCalibrations(calibrations), 3749);
}
