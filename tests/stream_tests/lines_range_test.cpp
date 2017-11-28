#include <sstream>
#include <vector>
#include <algorithm>
#include "algol/stream/lines_range.hpp"

#include "gtest/gtest.h"

using lines_range = algol::stream::lines_range;

class lines_range_fixture : public ::testing::Test {
protected:
  std::istringstream sin_empty {""};
  lines_range lr_empty {sin_empty};
  std::istringstream sin {"line 1\nline 2\nline 3\nline 4"};
  lines_range lr {sin};
};

TEST_F(lines_range_fixture, empty)
{
  EXPECT_EQ(std::begin(lr_empty), std::end(lr_empty));
  EXPECT_FALSE(lr_empty);
  EXPECT_TRUE(!lr_empty);
}

TEST_F(lines_range_fixture, not_empty)
{
  EXPECT_NE(std::begin(lr), std::end(lr));
  EXPECT_TRUE(lr);
  EXPECT_FALSE(!lr);
}

TEST_F(lines_range_fixture, iteration)
{
  std::vector<std::string> val;
  std::copy(std::begin(lr), std::end(lr), std::back_inserter(val));
  EXPECT_FALSE(lr);
  EXPECT_EQ(val.size(), static_cast<std::size_t>(4));

  auto minmax = std::minmax_element(std::begin(val), std::end(val));
  EXPECT_EQ(*minmax.first, "line 1");
  EXPECT_EQ(*minmax.second, "line 4");
}