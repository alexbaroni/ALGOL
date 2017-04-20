#include <array>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <sstream>
#include "algol/io/pprint.hpp"

#include "gtest/gtest.h"

#define COMMA ,

PPRINT_DEFAULT_DECORATION(T[N], "[", ";", "]", class T, std::size_t N)
PPRINT_DEFAULT_DECORATION(std::array<T COMMA N>, "[", "; ", "]", class T, std::size_t N)
PPRINT_DEFAULT_DECORATION(std::pair<T COMMA U>, "(", ", ", ")", class T, class U)

namespace pprint = algol::io::pprint;

class pprint_fixture : public ::testing::Test
{
protected:
  std::array<int32_t, 10> array_ {2, 3, 5, 1, 10, 9, 4, 6, 8, 7};
  std::pair<uint32_t, int32_t> pair_ {1, -1};
  float carray_[5] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
  std::vector<int> vector_ {155, 32, 26, 0};
  std::vector<int> vector_a_ {2, 3, 4, 1}, vector_b_ {4, 6, 1, 2};
  std::vector<std::vector<int>> vector_c_ {vector_a_, vector_b_, vector_b_, vector_a_};
  std::vector<std::vector<int>> matrix_ {{1, 2, 3},
                                         {4, 5, 6},
                                         {7, 8, 9}};
  std::map<int, int> matrix_of_pairs_ {std::make_pair<const int, int>(1, 1),
                                       std::make_pair<const int, int>(2, 4),
                                       std::make_pair<const int, int>(3, 7)};
  std::set<int> set_ {1, 5, 3, 2, 9, 6, 7};
  std::list<int> list_ {12, 12, 15, 8, 2, 1, 4};
  std::vector<std::map<int, int>> vector_of_map_ {matrix_of_pairs_, matrix_of_pairs_, matrix_of_pairs_};
};

TEST_F(pprint_fixture, test_array_print) {
  std::ostringstream os;
  os << array_;
  EXPECT_STREQ(os.str().c_str(), "[2; 3; 5; 1; 10; 9; 4; 6; 8; 7]");
}

TEST_F(pprint_fixture, test_pair_print) {
  std::ostringstream os;
  os << pair_;
  EXPECT_STREQ(os.str().c_str(), "(1, -1)");
}

TEST_F(pprint_fixture, test_carray_print) {
  std::ostringstream os;
  os << carray_;
  EXPECT_STREQ(os.str().c_str(), "[1.1;2.2;3.3;4.4;5.5]");
}

TEST_F(pprint_fixture, test_vector_print) {
  std::ostringstream os, os1, os2;
  os << vector_;
  EXPECT_STREQ(os.str().c_str(), "155, 32, 26, 0");
  os1 << pprint::decoration<std::vector<int>>("[[  ", " :: ", "  ]]");
  os1 << vector_a_ << vector_b_;
  EXPECT_STREQ(os1.str().c_str(), "[[  2 :: 3 :: 4 :: 1  ]][[  4 :: 6 :: 1 :: 2  ]]");
  os2 << vector_c_;
  EXPECT_STREQ(os2.str().c_str(), "2, 3, 4, 1, 4, 6, 1, 2, 4, 6, 1, 2, 2, 3, 4, 1");
}

TEST_F(pprint_fixture, test_matrix_print) {
  std::ostringstream os, os1;
  os << pprint::decoration<std::vector<std::vector<int>>>("\n") << matrix_;
  EXPECT_STREQ(os.str().c_str(), "1, 2, 3\n4, 5, 6\n7, 8, 9");

  os1 << pprint::decoration<std::vector<std::vector<int>>>("{", "\n", "}\n") << matrix_;
  EXPECT_STREQ(os1.str().c_str(), "{1, 2, 3\n4, 5, 6\n7, 8, 9}\n");
}

TEST_F(pprint_fixture, test_matrix_of_pairs_print) {
  std::ostringstream os;
  os << matrix_of_pairs_;
  EXPECT_STREQ(os.str().c_str(), "(1, 1), (2, 4), (3, 7)");
}

TEST_F(pprint_fixture, test_set_print) {
  std::ostringstream os;
  os << set_;
  EXPECT_STREQ(os.str().c_str(), "1, 2, 3, 5, 6, 7, 9");
}

TEST_F(pprint_fixture, test_list_print) {
  std::ostringstream os;
  os << list_;
  EXPECT_STREQ(os.str().c_str(), "12, 12, 15, 8, 2, 1, 4");
}

TEST_F(pprint_fixture, test_vector_of_map_print) {
  std::ostringstream os;
  os << pprint::decoration<std::map<int, int>>("{", " ", "}")
     << pprint::decoration<std::vector<std::map<int, int>>>("{ ", "; ", " }")
     << vector_of_map_;
  EXPECT_STREQ(os.str().c_str(), "{ {(1, 1) (2, 4) (3, 7)}; {(1, 1) (2, 4) (3, 7)}; {(1, 1) (2, 4) (3, 7)} }");
}