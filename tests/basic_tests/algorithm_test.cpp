#include <type_traits>
#include "algol/ds/array/array.hpp"
#include "algol/algorithms/algorithm.hpp"

#include "gtest/gtest.h"

constexpr std::size_t identity (std::size_t x)
{ return x; }

static constexpr int test_swap ()
{
  int a = 10;
  int b = 11;
  algol::algorithms::swap(a, b);
  return b;
}

template <typename T, std::size_t N>
constexpr auto test_reverse (std::array<T, N> array)
{
  algol::algorithms::reverse(std::begin(array), std::end(array));
  return array[0];
}

constexpr auto test_reverse ()
{
  std::array arr2 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  algol::algorithms::reverse(std::begin(arr2), std::end(arr2));
  return arr2[0];
}

constexpr auto lr = [] (auto i) { return i; };

constexpr auto test_reverse2 ()
{
  auto arr2 = algol::ds::fill_array<10>(lr);
  algol::algorithms::reverse(std::begin(arr2), std::end(arr2));
  return arr2[0];
}

constexpr auto test_rotate ()
{
  std::array arr2 {2, 4, 6, 8, 5, 9, 7};
  return *algol::algorithms::rotate(std::begin(arr2) + 2, std::begin(arr2) + 4, std::end(arr2));
}

static_assert(test_swap() == 10);
static_assert(sizeof(algol::ds::fill_array<100>(identity)) > 1, "NOT CONSTEXPR");
static_assert(std::is_literal_type_v<typename std::array<int, 10>::iterator>);
static_assert(test_reverse(std::array<int, 4>{1, 2, 3, 4}) == 4, "constexpr reverse not working");
static_assert(test_reverse() == 10, "constexpr reverse not working");
static_assert(test_reverse2() == 9, "constexpr reverse not working");
static_assert(test_rotate() == 6, "constexpr rotate not working");

class algorithm_fixture : public ::testing::Test {
protected:
  std::array<std::size_t, 100> array = algol::ds::fill_array<100>(identity);
};

TEST_F(algorithm_fixture, swap)
{
  ASSERT_EQ(test_swap(), 10);
}

TEST_F(algorithm_fixture, reverse)
{
  ASSERT_EQ(test_reverse(array), 99u);
}

TEST_F(algorithm_fixture, rotate)
{
  ASSERT_EQ(test_rotate(), 6);
}

