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
  ASSERT_THROW({char i = algol::to<char>("1000"); i++; }, std::system_error);
  ASSERT_THROW({unsigned char i = algol::to<unsigned char>("-1"); i++; }, std::system_error);
  ASSERT_THROW({int i = algol::to<int>("1235467890123456789012345"); i++; }, std::system_error);
  ASSERT_THROW({unsigned int i = algol::to<unsigned int>("-1"); i++; }, std::system_error);
  ASSERT_THROW({long i = algol::to<long>("1235467890123456789012345"); i++; }, std::system_error);
  ASSERT_THROW({unsigned long i = algol::to<unsigned long>("-1"); i++; }, std::system_error);
  ASSERT_THROW({long long i = algol::to<long long>("1235467890123456789012345"); i++; }, std::system_error);
  ASSERT_THROW({unsigned long long i = algol::to<unsigned long long>("-1"); i++; }, std::system_error);
  ASSERT_THROW({float i = algol::to<float>("3.40282e+039"); i++; }, std::system_error);
  ASSERT_THROW({double i = algol::to<double>("3.40282e+339"); i++; }, std::system_error);
  ASSERT_THROW({long double i = algol::to<long double>("3.40282e+33339"); i++; }, std::system_error);
  ASSERT_THROW({float i = algol::to<float>("DEFGG"); i++; }, std::system_error);
  ASSERT_THROW({double i = algol::to<double>("DEFGG"); i++; }, std::system_error);
  ASSERT_THROW({long double i = algol::to<long double>("DEFGG"); i++; }, std::system_error);
  ASSERT_THROW({long i = algol::to<long>("DEFGG"); i++; }, std::system_error);
  ASSERT_THROW({int i = algol::to<int>("DEFGG"); i++; }, std::system_error);
  ASSERT_THROW({char i = algol::to<char>("DEFGG"); i++; }, std::system_error);
}