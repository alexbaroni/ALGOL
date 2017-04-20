#include <sstream>
#include "algol/perf/operation_counter.hpp"

#include "gtest/gtest.h"

using operation_counter = algol::perf::operation_counter<std::int32_t, std::uint64_t>;

class operation_counter_fixture : public ::testing::Test {
  virtual void SetUp() {
    // to avoid array_ construction operation
    operation_counter::reset();
  }

protected:
  std::array<operation_counter, 10> array_{2, 3, 5, 1, 10, 9, 4, 6, 8, 7};
};

TEST_F(operation_counter_fixture, test_ctor_count) {
  operation_counter c{0};
  operation_counter::value_type v = c;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(0));
  EXPECT_TRUE(v == c);
  EXPECT_EQ(operation_counter::assignments(), static_cast<operation_counter::counter_type>(1));
  EXPECT_EQ(operation_counter::accesses(), static_cast<operation_counter::counter_type>(1));
}

TEST_F(operation_counter_fixture, test_copy_ctor_count) {
  operation_counter c = array_[0];
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(2));
  EXPECT_EQ(operation_counter::assignments(), static_cast<operation_counter::counter_type>(1));
}

TEST_F(operation_counter_fixture, test_eq_op_count) {
  operation_counter c{0};
  c = array_[0];
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(2));
  EXPECT_EQ(operation_counter::assignments(), static_cast<operation_counter::counter_type>(2));
}

TEST_F(operation_counter_fixture, test_assignment_count) {
  for (auto v : array_) {
    if (v == 6)
      break;
  }

  EXPECT_EQ(operation_counter::assignments(), static_cast<operation_counter::counter_type>(8));
}

TEST_F(operation_counter_fixture, test_move_ctor_count) {
  operation_counter c;
  c = std::move(array_[0]);
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(2));
  EXPECT_EQ(operation_counter::moves(), static_cast<operation_counter::counter_type>(1));
}

TEST_F(operation_counter_fixture, test_move_eq_count) {
  operation_counter c{0};
  operation_counter c1{1};
  c = std::move(c1);
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(1));
  EXPECT_EQ(operation_counter::moves(), static_cast<operation_counter::counter_type>(1));
}

TEST_F(operation_counter_fixture, test_op_plus_count) {
  operation_counter c;
  operation_counter c1{3};
  operation_counter c2{2};
  c = c1 + c2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(5));
  c += 2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(7));
  c = 2 + c;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(9));
  EXPECT_EQ(operation_counter::additions(), static_cast<operation_counter::counter_type>(3));
}

TEST_F(operation_counter_fixture, test_unary_plus_count) {
  operation_counter c{1};
  c = +c;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(1));
  EXPECT_EQ(operation_counter::unary_plus(), static_cast<operation_counter::counter_type>(1));
}

TEST_F(operation_counter_fixture, test_unary_minus_count) {
  operation_counter c{1};
  c = -c;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(-1));
  EXPECT_EQ(operation_counter::unary_minus(), static_cast<operation_counter::counter_type>(1));
}

TEST_F(operation_counter_fixture, test_not_count) {
  operation_counter c{0};
  c = !c;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(1));
  EXPECT_EQ(operation_counter::nots(), static_cast<operation_counter::counter_type>(1));
}

TEST_F(operation_counter_fixture, test_complement_count) {
  operation_counter c{0};
  c = ~c;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(-1));
  EXPECT_EQ(operation_counter::complements(), static_cast<operation_counter::counter_type>(1));
}

TEST_F(operation_counter_fixture, test_increment_count) {
  operation_counter c{1};
  c++;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(2));
  ++c;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(3));
  EXPECT_EQ(operation_counter::increments(), static_cast<operation_counter::counter_type>(2));
}

TEST_F(operation_counter_fixture, test_decrement_count) {
  operation_counter c{1};
  c--;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(0));
  --c;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(-1));
  EXPECT_EQ(operation_counter::decrements(), static_cast<operation_counter::counter_type>(2));
}

TEST_F(operation_counter_fixture, test_op_minus_count) {
  operation_counter c;
  operation_counter c1{3};
  operation_counter c2{2};
  c = c2 - c1;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(-1));
  c -= 2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(-3));
  c = 2 - c;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(5));
  EXPECT_EQ(operation_counter::subtractions(), static_cast<operation_counter::counter_type>(3));
}

TEST_F(operation_counter_fixture, test_op_mult_count) {
  operation_counter c;
  operation_counter c1{3};
  operation_counter c2{2};
  c = c2 * c1;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(6));
  c *= 2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(12));
  c = 2 * c;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(24));
  EXPECT_EQ(operation_counter::multiplications(), static_cast<operation_counter::counter_type>(3));
}

TEST_F(operation_counter_fixture, test_op_div_count) {
  operation_counter c;
  operation_counter c1{24};
  operation_counter c2{2};
  c = c1 / c2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(12));
  c /= 2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(6));
  c = 24 / c;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(4));
  EXPECT_EQ(operation_counter::divisions(), static_cast<operation_counter::counter_type>(3));
}

TEST_F(operation_counter_fixture, test_op_mod_count) {
  operation_counter c;
  operation_counter c1{7};
  operation_counter c2{4};
  operation_counter c3{5};
  c = c1 % c2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(3));
  c %= 3;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(0));
  c = 24 % c3;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(4));
  EXPECT_EQ(operation_counter::moduli(), static_cast<operation_counter::counter_type>(3));
}

TEST_F(operation_counter_fixture, test_and_count) {
  operation_counter c{12};
  c = c & 4;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(4));
  c &= 2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(0));
  EXPECT_EQ(operation_counter::ands(), static_cast<operation_counter::counter_type>(2));
}

TEST_F(operation_counter_fixture, test_or_count) {
  operation_counter c{12};
  c = c | 2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(14));
  c |= 1;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(15));
  EXPECT_EQ(operation_counter::ors(), static_cast<operation_counter::counter_type>(2));
}

TEST_F(operation_counter_fixture, test_xor_count) {
  operation_counter c{12};
  c = c ^ 4;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(8));
  c ^= 1;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(9));
  EXPECT_EQ(operation_counter::xors(), static_cast<operation_counter::counter_type>(2));
}

TEST_F(operation_counter_fixture, test_shift_left_count) {
  operation_counter c{1};
  c = c << 2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(4));
  c <<= 2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(16));
  EXPECT_EQ(operation_counter::left_shifts(), static_cast<operation_counter::counter_type>(2));
}

TEST_F(operation_counter_fixture, test_shift_right_count) {
  operation_counter c{20};
  c = c >> 1;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(10));
  c >>= 2;
  EXPECT_EQ(c, static_cast<operation_counter::value_type>(2));
  EXPECT_EQ(operation_counter::right_shifts(), static_cast<operation_counter::counter_type>(2));
}

TEST_F(operation_counter_fixture, test_eq_comp_count) {
  operation_counter c{20};
  operation_counter c1{2};
  EXPECT_TRUE(c == c);
  EXPECT_FALSE(c == c1);
  EXPECT_TRUE(c == 20);
  EXPECT_TRUE(20 == c);
  EXPECT_FALSE(c == 21);
  EXPECT_FALSE(21 == c);
  EXPECT_EQ(operation_counter::equal_comparisons(), static_cast<operation_counter::counter_type>(6));
}

TEST_F(operation_counter_fixture, test_not_eq_comp_count) {
  operation_counter c{20};
  operation_counter c1{2};
  EXPECT_FALSE(c != c);
  EXPECT_TRUE(c != c1);
  EXPECT_FALSE(c != 20);
  EXPECT_FALSE(20 != c);
  EXPECT_TRUE(c != 21);
  EXPECT_TRUE(21 != c);
  EXPECT_EQ(operation_counter::equal_comparisons(), static_cast<operation_counter::counter_type>(6));
}

TEST_F(operation_counter_fixture, test_lt_comp_count) {
  operation_counter c{20};
  operation_counter c1{2};
  EXPECT_FALSE(c < c);
  EXPECT_TRUE(c1 < c);
  EXPECT_FALSE(c < c1);
  EXPECT_TRUE(c < 21);
  EXPECT_FALSE(c < 3);
  EXPECT_FALSE(21 < c);
  EXPECT_TRUE(3 < c);
  EXPECT_EQ(operation_counter::less_comparisons(), static_cast<operation_counter::counter_type>(7));
}

TEST_F(operation_counter_fixture, test_gt_comp_count) {
  operation_counter c{20};
  operation_counter c1{2};
  EXPECT_FALSE(c > c);
  EXPECT_FALSE(c1 > c);
  EXPECT_TRUE(c > c1);
  EXPECT_FALSE(c > 21);
  EXPECT_TRUE(c > 3);
  EXPECT_TRUE(21 > c);
  EXPECT_FALSE(3 > c);
  EXPECT_EQ(operation_counter::great_comparisons(), static_cast<operation_counter::counter_type>(7));
}

TEST_F(operation_counter_fixture, test_lt_eq_comp_count) {
  operation_counter c{20};
  operation_counter c1{2};
  EXPECT_TRUE(c <= c);
  EXPECT_TRUE(c1 <= c);
  EXPECT_FALSE(c <= c1);
  EXPECT_TRUE(c <= 20);
  EXPECT_FALSE(c <= 3);
  EXPECT_TRUE(20 <= c);
  EXPECT_TRUE(3 <= c);
  EXPECT_EQ(operation_counter::less_eq_comparisons(), static_cast<operation_counter::counter_type>(7));
}

TEST_F(operation_counter_fixture, test_gt_eq_comp_count) {
  operation_counter c{20};
  operation_counter c1{2};
  EXPECT_TRUE(c >= c);
  EXPECT_FALSE(c1 >= c);
  EXPECT_TRUE(c >= c1);
  EXPECT_FALSE(c >= 21);
  EXPECT_TRUE(c >= 20);
  EXPECT_TRUE(20 >= c);
  EXPECT_FALSE(3 >= c);
  EXPECT_EQ(operation_counter::great_eq_comparisons(), static_cast<operation_counter::counter_type>(7));
}