#include "algol/result/to.hpp"

#include "gtest/gtest.h"

class to_fixture : public ::testing::Test {
};

TEST_F(to_fixture, char_test) {
  EXPECT_EQ(algol::to<char>("10"), 10);
  EXPECT_EQ(algol::to<unsigned char>("11"), 11);
  EXPECT_EQ(algol::to<wchar_t>("11001"), 11001);
  EXPECT_EQ(algol::to<char16_t>("11002"), 11002);
  EXPECT_EQ(algol::to<char32_t>("11111111"), 11111111u);
}

TEST_F(to_fixture, int_test) {
  EXPECT_EQ(algol::to<short>("11111"), 11111);
  EXPECT_EQ(algol::to<unsigned short>("65535"), 65535u);
  EXPECT_EQ(algol::to<int>("11111111"), 11111111);
  EXPECT_EQ(algol::to<unsigned int>("11111111"), 11111111u);
  EXPECT_EQ(algol::to<std::int16_t>("11111"), 11111);
}

TEST_F(to_fixture, long_test) {
  EXPECT_EQ(algol::to<long>("11111111"), 11111111);
  EXPECT_EQ(algol::to<unsigned long>("11111111"), 11111111u);
  EXPECT_EQ(algol::to<long long>("11111111444551"), 11111111444551);
  EXPECT_EQ(algol::to<unsigned long long>("11111111444551"), 11111111444551u);
}

TEST_F(to_fixture, fp_test) {
  EXPECT_EQ(algol::to<float>("1.25"), 1.25f);
  EXPECT_EQ(algol::to<double>("1.25"), 1.25);
  EXPECT_EQ(algol::to<long double>("1.25"), 1.25);
}

TEST_F(to_fixture, exception_test) {
  ASSERT_THROW({int i = algol::to<int>("DEFGG"); i++; }, std::invalid_argument);
}