#include <system_error>
#include <exception>
#include "algol/result/result.hpp"

#include "gtest/gtest.h"

class result_fixture : public ::testing::Test {
protected:
  algol::result<int> res_1{1};
  algol::result<int> res_err{std::make_error_code(std::errc::invalid_argument)};
  //auto res_err = algol::make_result(std::make_error_code(std::errc::invalid_argument));
  algol::result<int> res_exc{std::make_exception_ptr(std::invalid_argument{"invalid argument"})};
};

TEST_F(result_fixture, result) {
  EXPECT_EQ(res_1, 1);
  ASSERT_TRUE(res_1);
  ASSERT_TRUE(res_1.has_value());
  ASSERT_FALSE(res_1.has_error());
  ASSERT_FALSE(res_1.has_exception());
  algol::result<int> res_2 = res_1;
  EXPECT_EQ(res_2, 1);
  ASSERT_TRUE(res_2);
  ASSERT_TRUE(res_2.has_value());
  algol::result<int> res_3 = 3;
  swap(res_1, res_3);
  EXPECT_EQ(res_1, 3);
  EXPECT_EQ(res_3, 1);
}

TEST_F(result_fixture, error_result) {
  ASSERT_FALSE(res_err.has_value());
  ASSERT_TRUE(res_err.has_error());
  ASSERT_FALSE(res_err.has_exception());
  ASSERT_THROW({
                 int i = res_err;
                 i++;
               }, std::system_error);
  swap(res_err, res_1);
  EXPECT_EQ(res_err, 1);
  ASSERT_TRUE(res_err);
  ASSERT_TRUE(res_err.has_value());
  ASSERT_FALSE(res_err.has_error());
  ASSERT_FALSE(res_err.has_exception());
  ASSERT_FALSE(res_1.has_value());
  ASSERT_TRUE(res_1.has_error());
  ASSERT_FALSE(res_1.has_exception());
  ASSERT_THROW({
                 int i = res_1;
                 i++;
               }, std::system_error);
}

TEST_F(result_fixture, exception_result) {
  ASSERT_FALSE(res_exc.has_value());
  ASSERT_FALSE(res_exc.has_error());
  ASSERT_TRUE(res_exc.has_exception());
  ASSERT_THROW({
                 int i = res_exc;
                 i++;
               }, std::invalid_argument);
  swap(res_exc, res_1);
  EXPECT_EQ(res_exc, 1);
  ASSERT_TRUE(res_exc);
  ASSERT_TRUE(res_exc.has_value());
  ASSERT_FALSE(res_exc.has_error());
  ASSERT_FALSE(res_exc.has_exception());
  ASSERT_FALSE(res_1.has_value());
  ASSERT_FALSE(res_1.has_error());
  ASSERT_TRUE(res_1.has_exception());
  ASSERT_THROW({
                 int i = res_1;
                 i++;
               }, std::invalid_argument);
}

TEST_F(result_fixture, compare_with_result) {
  algol::result<int> res_2{2};
  algol::result<int> res_3{1};
  ASSERT_TRUE(res_1 == res_3);
  ASSERT_TRUE(res_3 == res_1);
  ASSERT_FALSE(res_2 == res_3);
  ASSERT_FALSE(res_3 == res_2);
  ASSERT_TRUE(res_1 != res_2);
  ASSERT_TRUE(res_2 != res_1);
  ASSERT_FALSE(res_1 != res_3);
  ASSERT_FALSE(res_3 != res_1);
  ASSERT_TRUE(res_1 < res_2);
  ASSERT_TRUE(res_2 > res_1);
  ASSERT_TRUE(res_1 <= res_3);
  ASSERT_TRUE(res_2 >= res_1);
}


TEST_F(result_fixture, compare_with_t) {
  algol::result<int> res_2{2};
  ASSERT_TRUE(res_1 == 1);
  ASSERT_TRUE(1 == res_1);
  ASSERT_FALSE(res_2 == 1);
  ASSERT_FALSE(1 == res_2);
  ASSERT_FALSE(res_1 != 1);
  ASSERT_FALSE(1 != res_1);
  ASSERT_TRUE(res_2 != 1);
  ASSERT_TRUE(1 != res_2);
  ASSERT_TRUE(res_1 < 2);
  ASSERT_TRUE(0 < res_1);
  ASSERT_TRUE(res_1 > 0);
  ASSERT_TRUE(2 > res_1);
  ASSERT_TRUE(res_1 <= 1);
  ASSERT_TRUE(1 <= res_1);
  ASSERT_TRUE(res_1 >= 1);
  ASSERT_TRUE(1 >= res_1);
}