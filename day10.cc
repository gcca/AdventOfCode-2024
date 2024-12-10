#include <unordered_set>

#include <gtest/gtest.h>

namespace std {
template <> struct hash<std::pair<std::size_t, std::size_t>> {
  std::size_t operator()(const std::pair<std::size_t, std::size_t> &p) const {
    auto h1 = std::hash<std::size_t>{}(p.first);
    auto h2 = std::hash<std::size_t>{}(p.second);
    return h1 ^ (h2 << 1);
  }
};
} // namespace std

static void
Traverse(const std::vector<std::string> &tmap, std::size_t i, std::size_t j,
         char c,
         std::unordered_set<std::pair<std::size_t, std::size_t>> &trailheads);

static void ScoreTrailhead(
    const std::vector<std::string> &tmap, std::size_t i, std::size_t j, char c,
    std::unordered_set<std::pair<std::size_t, std::size_t>> &trailheads) {
  Traverse(tmap, i - 1, j, c, trailheads);
  Traverse(tmap, i, j - 1, c, trailheads);
  Traverse(tmap, i + 1, j, c, trailheads);
  Traverse(tmap, i, j + 1, c, trailheads);
}

static void
Traverse(const std::vector<std::string> &tmap, std::size_t i, std::size_t j,
         char c,
         std::unordered_set<std::pair<std::size_t, std::size_t>> &trailheads) {
  if (i < tmap.size() and j < tmap[i].size() and tmap[i][j] == c) {
    if (c == '9')
      trailheads.emplace(i, j);
    else
      ScoreTrailhead(tmap, i, j, c + 1, trailheads);
  }
}

static std::size_t CountScoreTrailheads(const std::vector<std::string> &tmap) {
  std::size_t score = 0;

  for (std::size_t i = 0; i < tmap.size(); ++i)
    for (std::size_t j = 0; j < tmap[i].size(); ++j)
      if (tmap[i][j] == '0') {
        std::unordered_set<std::pair<std::size_t, std::size_t>> trailheads;
        ScoreTrailhead(tmap, i, j, '1', trailheads);
        score += trailheads.size();
      }

  return score;
}

TEST(AdventOfCode2024, Day10) {
  EXPECT_EQ(CountScoreTrailheads({
                "0123", //
                "1234", //
                "8765", //
                "9876"  //
            }),
            1);

  EXPECT_EQ(CountScoreTrailheads({
                "...0...", //
                "...1...", //
                "...2...", //
                "6543456", //
                "7.....7", //
                "8.....8", //
                "9.....9"  //
            }),
            2);

  EXPECT_EQ(CountScoreTrailheads({
                "..90..9", //
                "...1.98", //
                "...2..7", //
                "6543456", //
                "765.987", //
                "876....", //
                "987...."  //
            }),
            4);

  EXPECT_EQ(CountScoreTrailheads({
                "10..9..", //
                "2...8..", //
                "3...7..", //
                "4567654", //
                "...8..3", //
                "...9..2", //
                ".....01"  //
            }),
            3);

  EXPECT_EQ(CountScoreTrailheads({
                "89010123", //
                "78121874", //
                "87430965", //
                "96549874", //
                "45678903", //
                "32019012", //
                "01329801", //
                "10456732"  //
            }),
            36);
}
