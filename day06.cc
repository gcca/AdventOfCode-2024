#include <gtest/gtest.h>

static inline char *At(int x, int y, int width, std::string &map) {
  return &map.data()[x * width + y];
}

static inline void TurnRight(int &dx, int &dy) {
  int tmp = dx;
  dx = dy;
  dy = -tmp;
}

static std::size_t CountPositions(const int height, const int width,
                                  std::string map) {

  int pos = static_cast<int>(map.find('^'));
  int x = pos / width;
  int y = pos % width;

  int dx = -1;
  int dy = 0;

  std::size_t count = 1;

  while ((x >= 0 and x + dx < height) and (y >= 0 and y + dy < width)) {
    if (*At(x + dx, y + dy, width, map) == '#')
      TurnRight(dx, dy);

    *At(x, y, width, map) = 'X';

    if (*At(x += dx, y += dy, width, map) != 'X')
      count++;
  }

  return count;
}

TEST(AdventOfCode2024, Day06) {
  const std::string map = "....#....."
                          ".........#"
                          ".........."
                          "..#......."
                          ".......#.."
                          ".........."
                          ".#..^....."
                          "........#."
                          "#........."
                          "......#...";

  EXPECT_EQ(CountPositions(10, 10, map), 41);
}
