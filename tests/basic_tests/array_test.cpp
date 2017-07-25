#include "algol/ds/array/array.hpp"

#include "gtest/gtest.h"

constexpr std::size_t identity(std::size_t x) { return x; }
constexpr std::size_t doubling(std::size_t x) { return x << 1; }

class array_fixture : public ::testing::Test {
  static_assert(sizeof(algol::ds::fill_array<10000>(identity)) > 1, "NOT CONSTEXPR");
protected:
  std::array<std::size_t, 10000> array = algol::ds::fill_array<10000>(identity);
  std::array<std::size_t, 10000> array2 = algol::ds::fill_array<10000>(doubling);
};

TEST_F(array_fixture, fill_array) {
  ASSERT_EQ(array[0],  0u);
  ASSERT_EQ(array[9999], 9999u);
  ASSERT_EQ(array2[0],  0u);
  ASSERT_EQ(array2[9999], 19998u);
}
