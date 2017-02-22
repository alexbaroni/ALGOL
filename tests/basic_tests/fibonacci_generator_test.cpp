#include <vector>
#include <algorithm>
#include <numeric>

#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/fibonacci_generator.hpp"

#include "gtest/gtest.h"


using fibonacci_infinite_seq = algol::sequence::fibonacci_infinite_seq<uint32_t>;
using fibonacci_upto_n_seq = algol::sequence::fibonacci_upto_n_seq<uint32_t, 55>;
using fibonacci_first_n_seq = algol::sequence::fibonacci_first_n_seq<uint32_t, 10>;
using even_fibonacci_infinite_seq = algol::sequence::even_fibonacci_infinite_seq<uint32_t>;

class fibonacci_fixture : public ::testing::Test {
protected:
    fibonacci_infinite_seq inf_seq;
    fibonacci_upto_n_seq upto_n_seq;
    fibonacci_first_n_seq first_n_seq;
    even_fibonacci_infinite_seq even_inf_seq;
};

TEST_F(fibonacci_fixture, infinite) {
    std::vector<uint32_t> val;
    EXPECT_NE(std::begin(inf_seq), std::end(inf_seq));
    std::copy_n(std::begin(inf_seq), 10, std::back_inserter(val));
    ASSERT_EQ(val.size(), 10u);
    ASSERT_EQ(val, (std::vector<uint32_t >{1, 1, 2, 3, 5 ,8, 13, 21, 34, 55}));
}

TEST_F(fibonacci_fixture, upto_n) {
    std::vector<uint32_t> val;
    EXPECT_NE(std::begin(upto_n_seq), std::end(upto_n_seq));
    std::copy(std::begin(upto_n_seq), std::end(upto_n_seq), std::back_inserter(val));
    ASSERT_EQ(val.size(), 10u);
    ASSERT_EQ(val, (std::vector<uint32_t >{1, 1, 2, 3, 5 ,8, 13, 21, 34, 55}));
}

TEST_F(fibonacci_fixture, first_n) {
    std::vector<uint32_t> val;
    EXPECT_NE(std::begin(first_n_seq), std::end(first_n_seq));
    std::copy(std::begin(first_n_seq), std::end(first_n_seq), std::back_inserter(val));
    ASSERT_EQ(val.size(), 10u);
    ASSERT_EQ(val, (std::vector<uint32_t >{1, 1, 2, 3, 5 ,8, 13, 21, 34, 55}));
}

TEST_F(fibonacci_fixture, even_infinite) {
    std::vector<uint32_t> val;
    EXPECT_NE(std::begin(even_inf_seq), std::end(even_inf_seq));
    std::copy_n(std::begin(even_inf_seq), 11, std::back_inserter(val));
    ASSERT_EQ(val.size(), 11u);
    ASSERT_EQ(val, (std::vector<uint32_t >{2, 8, 34, 144, 610, 2584, 10946, 46368, 196418, 832040, 3524578}));
    uint32_t sum = std::accumulate(std::begin(val), std::end(val), 0);
    ASSERT_EQ(sum, 4613732u);
}
