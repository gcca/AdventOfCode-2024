#include <gtest/gtest.h>

static double Distance(std::pair<int, int> p, std::pair<int, int> q) {
  int x1 = p.first, y1 = p.second;
  int x2 = q.first, y2 = q.second;

  return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

static std::pair<int, int> Center(std::pair<int, int> p,
                                  std::pair<int, int> q) {
  double x1 = p.first, y1 = p.second;
  double x2 = q.first, y2 = q.second;

  return std::make_pair(std::round((x1 + x2) / 2), std::round((y1 + y2) / 2));
}

static std::pair<int, int> Direction(std::pair<int, int> p,
                                     std::pair<int, int> q) {
  double x1 = p.first, y1 = p.second;
  double x2 = q.first, y2 = q.second;

  return std::make_pair(std::round(x2 - x1), std::round(y2 - y1));
}

static int CountAntinodes(std::vector<std::string> map) {
  int antinodes = 0;

  std::size_t height = map.size(), width = map[0].size();
  int iheight = static_cast<int>(height), iwidth = static_cast<int>(width);

  std::unordered_map<int, std::vector<std::pair<int, int>>> nodes;

  for (std::size_t x = 0; x < height; ++x)
    for (std::size_t y = 0; y < width; ++y)
      if (map[x][y] != '.')
        nodes[map[x][y]].emplace_back(x, y);

  for (const auto &[_, pairs] : nodes) {

    for (std::size_t i = 0; i < pairs.size() - 1; ++i) {
      for (std::size_t j = i + 1; j < pairs.size(); ++j) {

        double distance = 1.2 * Distance(pairs[i], pairs[j]);

        std::pair<int, int> center = Center(pairs[i], pairs[j]);

        std::pair<int, int> direction = Direction(pairs[i], pairs[j]);

        double norm = std::sqrt(std::pow(direction.first, 2) +
                                std::pow(direction.second, 2));

        std::pair<int, int> p = std::make_pair(
            std::round(center.first + (direction.first * distance) / norm),
            std::round(center.second + (direction.second * distance) / norm));

        std::pair<int, int> q = std::make_pair(
            std::round(center.first - (direction.first * distance) / norm),
            std::round(center.second - (direction.second * distance) / norm));

        std::size_t px = static_cast<std::size_t>(p.first),
                    py = static_cast<std::size_t>(p.second);
        if (p.first >= 0 and p.first < iheight and p.second >= 0 and
            p.second < iwidth and map[px][py] == '.') {
          map[px][py] = '#';
          ++antinodes;
        }

        std::size_t qx = static_cast<std::size_t>(q.first),
                    qy = static_cast<std::size_t>(q.second);
        if (q.first >= 0 and q.first < iheight and q.second >= 0 and
            q.second < iwidth and map[qx][qy] == '.') {
          map[qx][qy] = '#';
          ++antinodes;
        }
      }
    }
  }

  return antinodes;
}

TEST(AdventOfCode2024, Day08) {
  std::vector<std::string> map = {{"............"}, //
                                  {"........0..."}, //
                                  {".....0......"}, //
                                  {".......0...."}, //
                                  {"....0......."}, //
                                  {"......A....."}, //
                                  {"............"}, //
                                  {"............"}, //
                                  {"........A..."}, //
                                  {".........A.."}, //
                                  {"............"}, //
                                  {"............"}};

  EXPECT_EQ(CountAntinodes(map), 14);
}
