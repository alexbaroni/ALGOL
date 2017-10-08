#include <array>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "algol/algorithms/recursion/permutation.hpp"

#include "gtest/gtest.h"

namespace rec = algol::algorithms::recursion;

class permutation_fixture : public ::testing::Test {
protected:
  std::string str{"ABC"};
  std::array<int, 3> arr {2,4,6};
  std::vector<int> vec {2,4,6};
};

TEST_F(permutation_fixture, array) {
  auto count = 0;
  for([[maybe_unused]] auto i : rec::permutations(std::begin(arr), std::end(arr))) {
    ++count;
  }
  ASSERT_EQ(count, 6);
}

TEST_F(permutation_fixture, string) {
  auto count = 0;
  for([[maybe_unused]] auto i : rec::permutations(std::begin(str), std::end(str))) {
    ++count;
  }
  ASSERT_EQ(count, 6);
}

TEST_F(permutation_fixture, vector) {
  auto count = 0;
  for([[maybe_unused]] auto i : rec::permutations(std::begin(vec), std::end(vec))) {
    ++count;
  }
  ASSERT_EQ(count, 6);
}