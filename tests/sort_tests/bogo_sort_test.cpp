#include <array>
#include <vector>
#include <string>
#include "algol/algorithms/sort/bogo_sort.hpp"

#include "gtest/gtest.h"

class bogo_sort_fixture : public ::testing::Test {
protected:
  std::array<int, 5> array {-3, 6, 5, 10, -2};
  std::array<int, 5> sorted_array {-3, -2, 5, 6, 10};
  std::vector<int> vec {-3, 6, 5, 10, -2};
  std::vector<int> sorted_vec {-3, -2, 5, 6, 10};
  std::string str{"BCA"};
  std::string sorted_str{"ABC"};
};

TEST_F(bogo_sort_fixture, random_sort_vec) {
  algol::algorithms::sort::random_bogo_sort(std::begin(vec), std::end(vec));
  ASSERT_EQ(vec[0],  -3);
  ASSERT_EQ(vec,  sorted_vec);
}

TEST_F(bogo_sort_fixture, random_sort_string) {
  algol::algorithms::sort::random_bogo_sort(std::begin(str), std::end(str));
  ASSERT_EQ(str[0], 'A');
  ASSERT_EQ(str,  sorted_str);
}

TEST_F(bogo_sort_fixture, random_sort_array) {
  algol::algorithms::sort::random_bogo_sort(std::begin(array), std::end(array));
  ASSERT_EQ(array[0],  -3);
  ASSERT_EQ(array,  sorted_array);
}

TEST_F(bogo_sort_fixture, deterministic_sort_vec) {
  algol::algorithms::sort::deterministic_bogo_sort(std::begin(vec), std::end(vec));
  ASSERT_EQ(vec[0],  -3);
  ASSERT_EQ(vec,  sorted_vec);
}

TEST_F(bogo_sort_fixture, deterministic_sort_string) {
  algol::algorithms::sort::deterministic_bogo_sort(std::begin(str), std::end(str));
  ASSERT_EQ(str[0], 'A');
  ASSERT_EQ(str,  sorted_str);
}

TEST_F(bogo_sort_fixture, deterministic_sort_array) {
  algol::algorithms::sort::deterministic_bogo_sort(std::begin(array), std::end(array));
  ASSERT_EQ(array[0],  -3);
  ASSERT_EQ(array,  sorted_array);
}