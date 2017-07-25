#include "algol/math/math.hpp"

#include "gtest/gtest.h"

class math_fixture : public ::testing::Test {
protected:
};

TEST_F(math_fixture, mod) {
  static_assert(algol::math::mod(15, 6) == 3);
  auto ri = algol::math::mod(15, 4);
  ASSERT_EQ(ri, 3);
  auto rf = algol::math::mod(15.0, 4.0);
  ASSERT_EQ(rf, 3.0);
}

TEST_F(math_fixture, nearly_equal) {
  ASSERT_TRUE(algol::math::nearly_equal(1.01, 1.01));
  ASSERT_FALSE(algol::math::nearly_equal(1.01, 1.02));
  ASSERT_FALSE(algol::math::nearly_equal(1.0001f, 1.0002f));
  ASSERT_FALSE(algol::math::nearly_equal(1.001f, 1.002f, 1000));
  ASSERT_TRUE(algol::math::nearly_equal(1.0001f, 1.0002f, 1000));
  ASSERT_FALSE(algol::math::nearly_equal(1.0000001, 1.0000002, 1000000));
  ASSERT_TRUE(algol::math::nearly_equal(1.0000001, 1.0000002, 1000000000));
}