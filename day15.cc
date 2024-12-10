#include <gtest/gtest.h>

static void MoveUp(std::size_t &x, std::size_t &) { x--; }

static void MoveDown(std::size_t &x, std::size_t &) { x++; }

static void MoveLeft(std::size_t &, std::size_t &y) { y--; }

static void MoveRight(std::size_t &, std::size_t &y) { y++; }

static std::size_t RobotPath(std::vector<std::string> box, std::string path) {
  std::size_t x = 0, y = 0;

  for (std::size_t i = 1; i < box.size() - 1; ++i)
    for (std::size_t j = 1; j < box[i].size() - 1; ++j)
      if (box[i][j] == '@') {
        x = j;
        y = i;
        break;
      }

  for (char c : path) {
    std::size_t dx = x, dy = y;

    void (*Ford)(std::size_t &, std::size_t &);
    void (*Back)(std::size_t &, std::size_t &);

    if (c == '^') {
      Ford = MoveUp;
      Back = MoveDown;
    } else if (c == 'v') {
      Ford = MoveDown;
      Back = MoveUp;
    } else if (c == '<') {
      Ford = MoveLeft;
      Back = MoveRight;
    } else if (c == '>') {
      Ford = MoveRight;
      Back = MoveLeft;
    } else
      continue;

    while (box[dx][dy] != '#' and box[dx][dy] != '.')
      Ford(dx, dy);

    if (box[dx][dy] == '#')
      continue;

    while (x != dx or y != dy) {
      std::size_t tx = dx, ty = dy;
      Back(dx, dy);

      box[tx][ty] = box[dx][dy];
    }
    box[x][y] = '.';
    Ford(x, y);
  }

  std::size_t gps = 0;

  for (std::size_t i = 1; i < box.size() - 1; ++i)
    for (std::size_t j = 1; j < box[i].size() - 1; ++j)
      if (box[i][j] == 'O')
        gps += i * 100 + j;

  return gps;
}

TEST(AdventOfCode2024, Day15) {
  EXPECT_EQ(RobotPath({"########", //
                       "#..O.O.#", //
                       "##@.O..#", //
                       "#...O..#", //
                       "#.#.O..#", //
                       "#...O..#", //
                       "#......#", //
                       "########"},
                      "<^^>>>vv<v>>v<<"),
            2028);

  EXPECT_EQ(RobotPath({"##########", //
                       "#.O.O.OOO#", //
                       "#........#", //
                       "#OO......#", //
                       "#OO@.....#", //
                       "#O#.....O#", //
                       "#O.....OO#", //
                       "#O.....OO#", //
                       "#OO....OO#", //
                       "##########"},
                      "<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<>"
                      "<<v<<<v^vv^v>^" //
                      "vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^"
                      "v>^<^^>>>^<v<v" //
                      "><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^"
                      "v^<v>v^^<^^vv<" //
                      "<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>"
                      "vvvv><>>v^<<^^^^^" //
                      "^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<"
                      "v>vvv>^<><<>^><" //
                      "^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><"
                      "<<^>>^v<v^v<v^" //
                      ">^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>"
                      "v^v><^^>>^<>vv^" //
                      "<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<>"
                      "<^^^>^^<>^>v<>" //
                      "^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^"
                      "v>^vvv<>^<><<v>" //
                      "v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>"
                      "v><v^<vv<>v^<<^"),
            10089);
}
