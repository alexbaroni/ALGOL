#include <vector>
#include <algorithm>

#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/sedgewick_gap_sequence_generator.hpp"

#include "gtest/gtest.h"

using sedgewick_gap_seq = algol::sequence::sedgewick_gap_seq<uint32_t>;

class sedgewick_gap_fixture : public ::testing::Test {
protected:
  sedgewick_gap_seq normal {1000};
  sedgewick_gap_seq edge {4193};
  sedgewick_gap_seq one_gap {8};
  sedgewick_gap_seq empty {};
};

TEST_F(sedgewick_gap_fixture, sequence_normal)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(normal), std::end(normal));
  std::copy(std::begin(normal), std::end(normal), std::back_inserter(val));
  ASSERT_EQ(val.size(), 5u);
  ASSERT_EQ(val, (std::vector<uint32_t>{281, 77, 23, 8, 1}));
}

TEST_F(sedgewick_gap_fixture, sequence_edge)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(edge), std::end(edge));
  std::copy(std::begin(edge), std::end(edge), std::back_inserter(val));
  ASSERT_EQ(val.size(), 6u);
  ASSERT_EQ(val, (std::vector<uint32_t>{1073, 281, 77, 23, 8, 1}));
}

TEST_F(sedgewick_gap_fixture, sequence_one_gap)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(one_gap), std::end(one_gap));
  std::copy(std::begin(one_gap), std::end(one_gap), std::back_inserter(val));
  ASSERT_EQ(val.size(), 1u);
  ASSERT_EQ(val, (std::vector<uint32_t>{1}));
}

TEST_F(sedgewick_gap_fixture, sequence_empty)
{
  std::vector<uint32_t> val;
  EXPECT_EQ(std::begin(empty), std::end(empty));
  std::copy(std::begin(empty), std::end(empty), std::back_inserter(val));
  ASSERT_EQ(val.size(), 0u);
  ASSERT_EQ(val, (std::vector<uint32_t>{}));
}

