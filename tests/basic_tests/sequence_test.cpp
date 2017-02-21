#include <sstream>
#include <vector>
#include <algorithm>
#include "algol/sequence/sequence.hpp"

#include "gtest/gtest.h"

template<typename T, T Max>
class iota_upto_n_generator
{
    mutable T current_;
protected:
    bool next() const
    {
        current_++;
        if (current_ > Max)
            return false;
        return true;
    }

    T const & dereference() const
    {
        return current_;
    }

    explicit operator bool() const // any objects left?
    {
        return current_ < Max;
    }

    bool operator!() const
    {
        return current_ >= Max;
    }

    iota_upto_n_generator() : current_(T{1}) {}
};


template<typename T>
using iota_upto_n_seq_empty =
algol::sequence::sequence<T, iota_upto_n_generator<T, 0>>;

template<typename T>
using iota_upto_n_seq =
algol::sequence::sequence<T, iota_upto_n_generator<T, 10>>;

class sequence_fixture : public ::testing::Test {
protected:
    iota_upto_n_seq_empty<uint32_t> seq_empty;
    iota_upto_n_seq<uint32_t> seq;
};

TEST_F(sequence_fixture, empty) {
    EXPECT_EQ(std::begin(seq_empty), std::end(seq_empty));
}

TEST_F(sequence_fixture, not_empty) {
    EXPECT_NE(std::begin(seq), std::end(seq));
}

TEST_F(sequence_fixture, iteration) {
    std::vector<uint32_t> val;
    std::copy(std::begin(seq), std::end(seq), std::back_inserter(val));

    auto minmax = std::minmax_element(std::begin(val), std::end(val));
    EXPECT_EQ(*minmax.first, 1u);
    EXPECT_EQ(*minmax.second, 10u);
}