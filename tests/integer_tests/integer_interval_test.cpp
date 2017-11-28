#include <sstream>
#include "algol/integer/integer_interval.hpp"

#include "gtest/gtest.h"

using interval = algol::integer::integer_interval<uint32_t>;

class integer_interval_fixture : public ::testing::Test {
protected:
  interval interval_empty;
  interval interval_1_10 {1, 10};
};

TEST_F(integer_interval_fixture, empty)
{
  EXPECT_EQ(width(interval_empty), 0u);
  EXPECT_EQ(lower(interval_empty), 0u);
  EXPECT_EQ(upper(interval_empty), 0u);
  EXPECT_TRUE(empty(interval_empty));
  EXPECT_FALSE(in(2u, interval_empty));
  EXPECT_FALSE(in(0u, interval_empty));
}

TEST_F(integer_interval_fixture, not_empty)
{
  EXPECT_EQ(width(interval_1_10), 10u);
  EXPECT_EQ(lower(interval_1_10), 1u);
  EXPECT_EQ(upper(interval_1_10), 10u);
  EXPECT_FALSE(empty(interval_1_10));
  EXPECT_TRUE(in(1u, interval_1_10));
  EXPECT_TRUE(in(2u, interval_1_10));
  EXPECT_TRUE(in(10u, interval_1_10));
  EXPECT_FALSE(in(0u, interval_1_10));
}

TEST_F(integer_interval_fixture, read_from_istream)
{
  interval interval_5_10;
  std::istringstream sin {"[5, 10]"};
  sin >> interval_5_10;
  EXPECT_EQ(width(interval_5_10), 6u);
  EXPECT_EQ(lower(interval_5_10), 5u);
  EXPECT_EQ(upper(interval_5_10), 10u);
  EXPECT_FALSE(empty(interval_5_10));
  EXPECT_TRUE(in(5u, interval_5_10));
  EXPECT_TRUE(in(10u, interval_5_10));
  EXPECT_FALSE(in(0u, interval_5_10));
  sin.str("(5;10)");
  sin >> interval_5_10;
  EXPECT_EQ(lower(interval_5_10), 5u);
  EXPECT_EQ(upper(interval_5_10), 10u);
}

TEST_F(integer_interval_fixture, write_to_ostream)
{
  std::ostringstream os;
  os << interval_1_10;
  EXPECT_STREQ(os.str().c_str(), "[1,10]");
}