#include <numeric>

#include <gtest/gtest.h>

static bool HasFreeBlocks(auto it, auto end) {
  while (++it != end)
    if (*it != '.')
      return true;
  return false;
}

static std::size_t Checksum(const std::string &diskmap) {
  std::string blocks;
  blocks.reserve(std::transform_reduce(
      diskmap.begin(), diskmap.end(), 0UL, std::plus<>(),
      [](char c) { return static_cast<std::size_t>(c); }));

  bool is_file = true;
  char IDn = 48;

  for (const auto &t : diskmap) {
    std::size_t times = static_cast<std::size_t>(t) - 48;

    const char c = is_file ? IDn++ : '.';

    while (times--)
      blocks.push_back(c);

    is_file = !is_file;
  }

  auto rpos = blocks.rbegin();
  auto lpos = blocks.begin();

  while (HasFreeBlocks(lpos, blocks.end())) {
    while (*rpos == '.')
      ++rpos;

    while (*lpos != '.')
      ++lpos;

    *lpos++ = *rpos;
    *rpos++ = '.';
  }

  std::size_t checksum = 0;
  for (std::size_t i = 0; i < blocks.size() and blocks[i] != '.'; ++i)
    checksum += i * static_cast<std::size_t>(blocks[i] - 48);

  return checksum;
}

TEST(AdventOfCode2024, Day09) {
  EXPECT_EQ(Checksum("12345"), 60);
  EXPECT_EQ(Checksum("2333133121414131402"), 1928);
}
