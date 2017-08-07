#include <utility>
#include <system_error>
#include <exception>
#include "algol/result/result.hpp"

#include "gtest/gtest.h"

class result_fixture : public ::testing::Test {
protected:
  algol::result<int> res_err{std::make_error_code(std::errc::invalid_argument)};
  //auto res_err = algol::make_result(std::make_error_code(std::errc::invalid_argument));
  algol::result<int> res_exc{std::make_exception_ptr(std::invalid_argument{"invalid argument"})};
};

TEST_F(result_fixture, result) {
  auto res_1 = algol::make_result(1);
  EXPECT_EQ(res_1, 1);
  ASSERT_TRUE(res_1);
  ASSERT_TRUE(res_1.has_value());
  ASSERT_FALSE(res_1.has_error());
  ASSERT_FALSE(res_1.has_exception());
  auto res_2 = res_1;
  EXPECT_EQ(res_2, 1);
  ASSERT_TRUE(res_2);
  ASSERT_TRUE(res_2.has_value());
  auto res_3 = algol::make_result(3);
  swap(res_1, res_3);
  EXPECT_EQ(res_1, 3);
  EXPECT_EQ(res_3, 1);
}

TEST_F(result_fixture, error_result) {
  auto res_1 = algol::make_result(1);
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
  auto res_1 = algol::make_result(1);
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
  auto res_1 = algol::make_result(1);
  auto res_2 = algol::make_result(2);
  auto res_3 = algol::make_result(1);
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
  auto res_1 = algol::make_result(1);
  auto res_2 = algol::make_result(2);
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

TEST_F(result_fixture, in_place) {
  auto res = algol::result<int>{std::in_place, 2};
  ASSERT_TRUE(res == 2);
  auto res_2 = algol::result<std::vector<int>>{std::in_place, {2, 3, 4, 5}};
  ASSERT_EQ(static_cast<std::vector<int>>(res_2).size(), 4u);
  auto res_3 = algol::make_result<std::vector<int>>({2, 3, 4, 5});
  ASSERT_EQ(static_cast<std::vector<int>>(res_3).size(), 4u);
  auto res_4 = algol::make_result<std::pair<int, double>>(2, 3.0);
  ASSERT_EQ((static_cast<std::pair<int, double>>(res_4).second), 3.0);
}

TEST_F(result_fixture, structured_binding)
{
  auto res_3 = algol::make_result<std::vector<int>>({2, 3, 4, 5});
  auto [v] = res_3;
  ASSERT_EQ(v.size(), 4u);
  auto res_4 = algol::make_result<std::pair<int, double>>(2, 3.0);
  auto [p] = res_4;
  auto [i, d] = p;
  ASSERT_TRUE(i == 2 && d == 3.0);
//  auto re = algol::make_result(std::make_error_code(std::errc::invalid_argument));
//  auto [x] = re;
}