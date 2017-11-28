#include <vector>
#include <algorithm>

#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/halving_generator.hpp"

#include "gtest/gtest.h"

using halving_seq = algol::sequence::halving_seq<uint32_t>;

class halving_fixture : public ::testing::Test {
protected:
  halving_seq seq_even {10};
  halving_seq seq_odd {17};
};

TEST_F(halving_fixture, sequence_even)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(seq_even), std::end(seq_even));
  std::copy(std::begin(seq_even), std::end(seq_even), std::back_inserter(val));
  ASSERT_EQ(val.size(), 3u);
  ASSERT_EQ(val, (std::vector<uint32_t>{5, 2, 1}));
}

TEST_F(halving_fixture, sequence_odd)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(seq_odd), std::end(seq_odd));
  std::copy(std::begin(seq_odd), std::end(seq_odd), std::back_inserter(val));
  ASSERT_EQ(val.size(), 4u);
  ASSERT_EQ(val, (std::vector<uint32_t>{8, 4, 2, 1}));
}

