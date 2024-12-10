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

static void MarkGardenPlots(
    std::vector<std::string> &garden,
    std::vector<std::vector<std::size_t>> &region_map, std::size_t i,
    std::size_t j, std::size_t mark, char c,
    std::vector<std::unordered_set<std::pair<std::size_t, std::size_t>>>
        &plots) {
  if (region_map[i][j] or garden[i][j] != c)
    return;

  region_map[i][j] = mark;

  if (plots.size() < mark)
    plots.emplace_back();

  plots[mark - 1].emplace(i, j);

  if (i > 0)
    MarkGardenPlots(garden, region_map, i - 1, j, mark, c, plots);

  if (i < garden.size() - 1)
    MarkGardenPlots(garden, region_map, i + 1, j, mark, c, plots);

  if (j > 0)
    MarkGardenPlots(garden, region_map, i, j - 1, mark, c, plots);

  if (j < garden[i].size() - 1)
    MarkGardenPlots(garden, region_map, i, j + 1, mark, c, plots);
}

static std::size_t TotalPrice(std::vector<std::string> garden) {
  std::vector<std::vector<std::size_t>> region_map;
  region_map.reserve(garden.size());
  std::transform(garden.begin(), garden.end(), std::back_inserter(region_map),
                 [](const std::string &row) {
                   std::vector<std::size_t> r;
                   r.resize(row.size());
                   return r;
                 });

  std::vector<std::unordered_set<std::pair<std::size_t, std::size_t>>> plots;
  plots.reserve(garden.size() * garden[0].size());

  std::size_t mark = 1;
  for (std::size_t i = 0; i < garden.size(); i++)
    for (std::size_t j = 0; j < garden[i].size(); j++) {
      if (region_map[i][j] != 0)
        continue;
      MarkGardenPlots(garden, region_map, i, j, mark++, garden[i][j], plots);
    }

  std::size_t total = 0;

  for (const auto &plot : plots) {
    std::size_t area = plot.size();
    std::size_t perimeter = 0;

    for (const auto &p : plot) {
      std::size_t i = p.first;
      std::size_t j = p.second;

      if (i == 0 or i == garden.size() - 1)
        perimeter++;

      if (j == 0 or j == garden[i].size() - 1)
        perimeter++;

      if (i > 0 and region_map[i - 1][j] != region_map[i][j])
        perimeter++;

      if (i < garden.size() - 1 and region_map[i + 1][j] != region_map[i][j])
        perimeter++;

      if (j > 0 and region_map[i][j - 1] != region_map[i][j])
        perimeter++;

      if (j < garden[i].size() - 1 and region_map[i][j + 1] != region_map[i][j])
        perimeter++;
    }

    total += area * perimeter;
  }

  return total;
}

TEST(AdeventOfCode2024, Day12) {
  EXPECT_EQ(TotalPrice({        //
                        "AAAA", //
                        "BBCD", //
                        "BBCC", //
                        "EEEC"}),
            140);

  EXPECT_EQ(TotalPrice({
                "OOOOO", //
                "OXOXO", //
                "OOOOO", //
                "OXOXO", //
                "OOOOO"  //
            }),
            772);

  EXPECT_EQ(TotalPrice({              //
                        "RRRRIICCFF", //
                        "RRRRIICCCF", //
                        "VVRRRCCFFF", //
                        "VVRCCCJFFF", //
                        "VVVVCJJCFE", //
                        "VVIVCCJJEE", //
                        "VVIIICJJEE", //
                        "MIIIIIJJEE", //
                        "MIIISIJEEE", //
                        "MMMISSJEEE"}),
            1930);
}
