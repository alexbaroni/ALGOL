#include <vector>
#include <algorithm>

#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/collatz_generator.hpp"

#include "gtest/gtest.h"

using collatz_seq = algol::sequence::collatz_seq<uint32_t>;

class collatz_fixture : public ::testing::Test {
protected:
  collatz_seq seq_1 {1};
  collatz_seq seq_5 {5};
};

TEST_F(collatz_fixture, collatz_seq_1)
{
  std::vector<uint32_t> val;
  EXPECT_EQ(std::begin(seq_1), std::end(seq_1));
  std::copy(std::begin(seq_1), std::end(seq_1), std::back_inserter(val));
  ASSERT_EQ(val.size(), 0u);
  ASSERT_EQ(val, (std::vector<uint32_t>{}));
}

TEST_F(collatz_fixture, collatz_seq_5)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(seq_5), std::end(seq_5));
  std::copy(std::begin(seq_5), std::end(seq_5), std::back_inserter(val));
  ASSERT_EQ(val.size(), 6u);
  ASSERT_EQ(val, (std::vector<uint32_t>{5, 16, 8, 4, 2, 1}));
}
