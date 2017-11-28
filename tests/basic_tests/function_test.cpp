#include "algol/func/function.hpp"

#include "gtest/gtest.h"

class function_fixture : public ::testing::Test {
protected:
};

TEST_F(function_fixture, identity)
{
  int i {6};
  EXPECT_EQ(algol::identity(1), 1);
  EXPECT_NE(algol::identity(2), 1);
  EXPECT_EQ(algol::identity(i), 6);
}
