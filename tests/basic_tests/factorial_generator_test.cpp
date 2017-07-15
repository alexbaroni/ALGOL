#include <vector>
#include <algorithm>

#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/factorial_generator.hpp"

#include "gtest/gtest.h"

using factorial_infinite = algol::sequence::factorial_infinite_seq<uint32_t>;
using factorial_first_n = algol::sequence::factorial_first_n_seq<uint32_t>;

class factorial_fixture : public ::testing::Test {
protected:
  factorial_infinite inf_seq;
  factorial_first_n first_n_seq {6};
};

TEST_F(factorial_fixture, infinite)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(inf_seq), std::end(inf_seq));
  std::copy_n(std::begin(inf_seq), 5, std::back_inserter(val));
  ASSERT_EQ(val.size(), 5u);
  ASSERT_EQ(val, (std::vector<uint32_t>{1, 2, 6, 24, 120}));
}

TEST_F(factorial_fixture, first_n)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(first_n_seq), std::end(first_n_seq));
  std::copy(std::begin(first_n_seq), std::end(first_n_seq), std::back_inserter(val));
  ASSERT_EQ(val.size(), 6u);
  ASSERT_EQ(val, (std::vector<uint32_t>{1, 2, 6, 24, 120, 720}));
}
