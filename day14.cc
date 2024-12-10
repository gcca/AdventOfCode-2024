#include <gtest/gtest.h>

static std::size_t SafetyFactor(
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> robots,
    int height, int width, int times) {

  while (times--)
    for (auto &robot : robots) {
      auto &position = robot.first;
      auto &velocity = robot.second;

      position.first += velocity.first;
      position.second += velocity.second;

      if (position.first < 0)
        position.first = width + position.first;

      if (position.first >= width)
        position.first = position.first - width;

      if (position.second < 0)
        position.second = height + position.second;

      if (position.second >= height)
        position.second = position.second - height;
    }

  std::size_t q1 = 0, q2 = 0, q3 = 0, q4 = 0;

  for (auto &robot : robots)
    if (robot.first.first < width / 2 and robot.first.second < height / 2)
      q1++;
    else if (robot.first.first > width / 2 and robot.first.second < height / 2)
      q2++;
    else if (robot.first.first < width / 2 and robot.first.second > height / 2)
      q3++;
    else if (robot.first.first > width / 2 and robot.first.second > height / 2)
      q4++;

  return q1 * q2 * q3 * q4;
}

TEST(AdeventOfCode2024, Day14) {
  EXPECT_EQ(SafetyFactor({{{0, 4}, {3, -3}},
                          {{6, 3}, {-1, -3}},
                          {{10, 3}, {-1, 2}},
                          {{2, 0}, {2, -1}},
                          {{0, 0}, {1, 3}},
                          {{3, 0}, {-2, -2}},
                          {{7, 6}, {-1, -3}},
                          {{3, 0}, {-1, -2}},
                          {{9, 3}, {2, 3}},
                          {{7, 3}, {-1, 2}},
                          {{2, 4}, {2, -3}},
                          {{9, 5}, {-3, -3}}},
                         7, 11, 100),
            12);

  EXPECT_EQ(SafetyFactor({{{0, 4}, {3, -3}},
                          {{6, 3}, {-1, -3}},
                          {{10, 3}, {-1, 2}},
                          {{2, 0}, {2, -1}},
                          {{0, 0}, {1, 3}},
                          {{3, 0}, {-2, -2}},
                          {{7, 6}, {-1, -3}},
                          {{3, 0}, {-1, -2}},
                          {{9, 3}, {2, 3}},
                          {{7, 3}, {-1, 2}},
                          {{2, 4}, {2, -3}},
                          {{9, 5}, {-3, -3}}},
                         103, 101, 100),
            21);
}
