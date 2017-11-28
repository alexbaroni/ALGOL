#include <vector>
#include <algorithm>

#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/hibbard_gap_sequence_generator.hpp"

#include "gtest/gtest.h"

using hibbard_gap_seq = algol::sequence::hibbard_gap_seq<uint32_t>;

class hibbard_gap_fixture : public ::testing::Test {
protected:
  hibbard_gap_seq normal {1000};
  hibbard_gap_seq edge {511};
};

TEST_F(hibbard_gap_fixture, sequence_normal)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(normal), std::end(normal));
  std::copy(std::begin(normal), std::end(normal), std::back_inserter(val));
  ASSERT_EQ(val.size(), 9u);
  ASSERT_EQ(val, (std::vector<uint32_t>{511, 255, 127, 63, 31, 15, 7, 3, 1}));
}

TEST_F(hibbard_gap_fixture, sequence_edge)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(edge), std::end(edge));
  std::copy(std::begin(edge), std::end(edge), std::back_inserter(val));
  ASSERT_EQ(val.size(), 8u);
  ASSERT_EQ(val, (std::vector<uint32_t>{255, 127, 63, 31, 15, 7, 3, 1}));
}


