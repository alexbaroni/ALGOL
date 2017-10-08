#include <sstream>
#include <vector>
#include <algorithm>
#include "algol/stream/istream_range.hpp"

#include "gtest/gtest.h"

using istream_range = algol::stream::istream_range<uint32_t>;

class istream_range_fixture : public ::testing::Test {
protected:
  std::istringstream sin_empty{""};
  istream_range ir_empty{sin_empty};
  std::istringstream sin{"1 2 3 4 5 6"};
  istream_range ir{sin};
};

TEST_F(istream_range_fixture, empty) {
  EXPECT_EQ(std::begin(ir_empty), std::end(ir_empty));
  EXPECT_FALSE(ir_empty);
  EXPECT_TRUE(!ir_empty);
}

TEST_F(istream_range_fixture, not_empty) {
  EXPECT_NE(std::begin(ir), std::end(ir));
  EXPECT_TRUE(ir);
  EXPECT_FALSE(!ir);
}

TEST_F(istream_range_fixture, iteration) {
  std::vector<uint32_t> val;
  std::copy(std::begin(ir), std::end(ir), std::back_inserter(val));
  EXPECT_FALSE(ir);
  EXPECT_EQ(val.size(), static_cast<std::size_t>(6));

  auto minmax = std::minmax_element(std::begin(val), std::end(val));
  EXPECT_EQ(*minmax.first, 1u);
  EXPECT_EQ(*minmax.second, 6u);
}