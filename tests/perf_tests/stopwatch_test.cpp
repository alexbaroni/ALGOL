#include <sstream>
#include "algol/perf/stopwatch.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

using stopwatch_ns = algol::perf::stopwatch<std::chrono::nanoseconds>;
using stopwatch_us = algol::perf::stopwatch<std::chrono::microseconds>;
using stopwatch_ms = algol::perf::stopwatch<std::chrono::milliseconds>;

class stopwatch_fixture : public ::testing::Test {
protected:
  stopwatch_ns sw_ns;
  stopwatch_us sw_us;
  stopwatch_ms sw_ms;
};

TEST_F(stopwatch_fixture, elapsed_gt_zero) {
  EXPECT_GE(sw_ns.elapsed().count(), 0);
}

TEST_F(stopwatch_fixture, ostream_op_contains_ns) {
  std::ostringstream os;
  os << sw_ns;
  EXPECT_THAT(os.str(), testing::HasSubstr("elapsed:"));
  EXPECT_THAT(os.str(), testing::HasSubstr("ns"));
}

TEST_F(stopwatch_fixture, ostream_op_contains_us) {
  std::ostringstream os;
  os << sw_us;
  EXPECT_THAT(os.str(), testing::HasSubstr("elapsed:"));
  EXPECT_THAT(os.str(), testing::HasSubstr("us"));
}

TEST_F(stopwatch_fixture, ostream_op_contains_ms) {
  std::ostringstream os;
  os << sw_ms;
  EXPECT_THAT(os.str(), testing::HasSubstr("elapsed:"));
  EXPECT_THAT(os.str(), testing::HasSubstr("ms"));
}

