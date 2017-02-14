#include <sstream>
#include <algorithm>
#include "algol/integer/integer_interval_range.hpp"

#include "gtest/gtest.h"

using interval = algol::integer::integer_interval<uint32_t>;
using interval_range = algol::integer::integer_interval_range<interval::base_type>;

class integer_interval_range_fixture : public ::testing::Test {
protected:
    interval interval_empty;
    interval interval_1_10{1, 10};
    interval_range interval_range_empty{interval_empty};
    interval_range interval_range_1_10{interval_1_10};
};

TEST_F(integer_interval_range_fixture, empty) {
    EXPECT_EQ(std::begin(interval_range_empty), std::end(interval_range_empty));
    EXPECT_FALSE(interval_range_empty);
    EXPECT_TRUE(!interval_range_empty);
}

TEST_F(integer_interval_range_fixture, not_empty) {
    EXPECT_NE(std::begin(interval_range_1_10), std::end(interval_range_1_10));
    EXPECT_TRUE(interval_range_1_10);
    EXPECT_FALSE(!interval_range_1_10);
}

TEST_F(integer_interval_range_fixture, iteration) {
    std::ostringstream sout;
    EXPECT_TRUE(interval_range_1_10);
    std::copy(std::begin(interval_range_1_10),
              std::end(interval_range_1_10), std::ostream_iterator<interval_range::base_type>(sout, ","));
    EXPECT_STREQ(sout.str().c_str(), "1,2,3,4,5,6,7,8,9,10,");
    EXPECT_FALSE(interval_range_1_10);
}