#include <gtest/gtest.h>
#include <numeric>

class Grid {
public:
  Grid(int height, int width, const std::string &&letters)
      : height_{height}, width_{width}, letters_{letters} {}

  std::size_t WordSearch(const std::string &word) const {
    int count = 0;

    for (int i = 0; i < height_; ++i) {
      count += FindInDir(word, i, 0, 0, 1) +
               FindInDir(word, i, width_ - 1, 0, -1) +
               FindInDir(word, i, 0, 1, 1) +
               FindInDir(word, height_ - 1 - i, 0, -1, 1) +
               FindInDir(word, i, width_ - 1, 1, -1) +
               FindInDir(word, height_ - 2 - i, width_ - 1, -1, -1);
    }

    for (int i = 0; i < width_; ++i) {
      count += FindInDir(word, 0, i, 1, 0) +
               FindInDir(word, height_ - 1, i, -1, 0) +
               FindInDir(word, 0, i, 1, 1) +
               FindInDir(word, 0, width_ - 2 - i, 1, -1) +
               FindInDir(word, height_ - 1, i, -1, 1) +
               FindInDir(word, height_ - 1, width_ - 1 - i, -1, -1);
    }

    return static_cast<std::size_t>(count);
  }

private:
  int height_;
  int width_;
  std::string letters_;

  char At(int i, int j) const {
    return letters_[static_cast<std::size_t>(i * height_ + j)]; // unbound?
  }

  std::size_t FindInDir(const std::string &word, int i, int j, int di,
                        int dj) const {
    std::size_t count = 0, k = 0, wsize = word.size();

    while ((i >= 0 and i <= height_) and (j >= 0 and j <= width_)) {
      if (At(i, j) == word[k]) {
        ++k;
      } else {
        k = At(i, j) == word[0];
      }

      if (k == wsize) {
        ++count;
        k = 0;
      }

      i += di;
      j += dj;
    }

    return count;
  }
};

TEST(AdventOfCode2024, Day04) {
  const Grid grid{10, 10,
                  "MMMSXXMASM"
                  "MSAMXMSMSA"
                  "AMXSXMAAMM"
                  "MSAMASMSMX"
                  "XMASAMXAMM"
                  "XXAMMXXAMA"
                  "SMSMSASXSS"
                  "SAXAMASAAA"
                  "MAMMMXMMMM"
                  "MXMXAXMASX"};

  EXPECT_EQ(grid.WordSearch("XMAS"), 18);
}
