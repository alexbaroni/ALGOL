#include <vector>
#include <algorithm>

#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/arithmetic_progression_generator.hpp"

#include "gtest/gtest.h"

using arithmetic_progression_infinite = algol::sequence::arithmetic_progression_infinite_seq<uint32_t>;
using arithmetic_progression_first_n = algol::sequence::arithmetic_progression_first_n_seq<uint32_t>;

class arithmetic_progression_fixture : public ::testing::Test {
protected:
  arithmetic_progression_infinite inf_seq {5, 2};
  arithmetic_progression_first_n first_n_seq {2, 3, 6};
};

TEST_F(arithmetic_progression_fixture, infinite)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(inf_seq), std::end(inf_seq));
  std::copy_n(std::begin(inf_seq), 5, std::back_inserter(val));
  ASSERT_EQ(val.size(), 5u);
  ASSERT_EQ(val, (std::vector<uint32_t>{5, 7, 9, 11, 13}));
}

TEST_F(arithmetic_progression_fixture, first_n)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(first_n_seq), std::end(first_n_seq));
  std::copy(std::begin(first_n_seq), std::end(first_n_seq), std::back_inserter(val));
  ASSERT_EQ(val.size(), 6u);
  ASSERT_EQ(val, (std::vector<uint32_t>{2, 5, 8, 11, 14, 17}));
}
