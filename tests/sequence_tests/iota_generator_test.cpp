#include <vector>
#include <algorithm>

#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/iota_generator.hpp"

#include "gtest/gtest.h"

using iota_infinite_seq = algol::sequence::iota_infinite_seq<uint32_t>;
using iota_upto_n_seq = algol::sequence::iota_upto_n_seq<uint32_t>;

class iota_fixture : public ::testing::Test {
protected:
  iota_infinite_seq inf_seq;
  iota_upto_n_seq upto_n_seq {10};
};

TEST_F(iota_fixture, infinite)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(inf_seq), std::end(inf_seq));
  std::copy_n(std::begin(inf_seq), 5, std::back_inserter(val));
  ASSERT_EQ(val.size(), 5u);
  ASSERT_EQ(val, (std::vector<uint32_t>{1, 2, 3, 4, 5}));
}

TEST_F(iota_fixture, upto_n)
{
  std::vector<uint32_t> val;
  EXPECT_NE(std::begin(upto_n_seq), std::end(upto_n_seq));
  std::copy(std::begin(upto_n_seq), std::end(upto_n_seq), std::back_inserter(val));
  ASSERT_EQ(val.size(), 10u);
  ASSERT_EQ(val, (std::vector<uint32_t>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}
