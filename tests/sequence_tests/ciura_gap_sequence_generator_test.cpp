#include <vector>
#include <algorithm>

#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/ciura_gap_sequence_generator.hpp"

#include "gtest/gtest.h"

using ciura_gap_seq = algol::sequence::ciura_gap_seq<uint32_t>;

class ciura_gap_fixture : public ::testing::Test {
protected:
  ciura_gap_seq after_last {2000};
  ciura_gap_seq middle {500};
};

TEST_F(ciura_gap_fixture, sequence_after_last_element)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(after_last), std::end(after_last));
  std::copy(std::begin(after_last), std::end(after_last), std::back_inserter(val));
  ASSERT_EQ(val.size(), 9u);
  ASSERT_EQ(val, (std::vector<uint32_t>{1750, 701, 301, 132, 57, 23, 10, 4, 1}));
}

TEST_F(ciura_gap_fixture, sequence_middle)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(middle), std::end(middle));
  std::copy(std::begin(middle), std::end(middle), std::back_inserter(val));
  ASSERT_EQ(val.size(), 7u);
  ASSERT_EQ(val, (std::vector<uint32_t>{301, 132, 57, 23, 10, 4, 1}));
}

