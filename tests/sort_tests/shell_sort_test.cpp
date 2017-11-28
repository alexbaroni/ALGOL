#include <array>
#include <vector>
#include <string>
#include <forward_list>
#include "algol/algorithms/sort/shell_sort.hpp"

#include "gtest/gtest.h"

class shell_sort_fixture : public ::testing::Test {
protected:
  std::array<int, 5> array {-3, 6, 5, 10, -2};
  std::array<int, 5> sorted_array {-3, -2, 5, 6, 10};
  std::vector<int> vec {-3, 6, 5, 10, -2};
  std::vector<int> sorted_vec {-3, -2, 5, 6, 10};
  std::forward_list<int> lst {-3, 6, 5, 10, -2};
  std::forward_list<int> sorted_lst {-3, -2, 5, 6, 10};
  std::string str {"BCA"};
  std::string sorted_str {"ABC"};
  std::array<char, 10> x {'a', 'b', 'd', 'c', 'h', 'z', 'a', 'y', 'w', 'm'};
  std::array<char, 10> xs {'a', 'a', 'b', 'c', 'd', 'h', 'm', 'w', 'y', 'z'};
};

TEST_F(shell_sort_fixture, sort_vec)
{
  algol::algorithms::sort::shell_sort(std::begin(vec), std::end(vec));
  ASSERT_EQ(vec[0], -3);
  ASSERT_EQ(vec, sorted_vec);
}

TEST_F(shell_sort_fixture, sort_string)
{
  algol::algorithms::sort::shell_sort(std::begin(str), std::end(str));
  ASSERT_EQ(str[0], 'A');
  ASSERT_EQ(str, sorted_str);
}

TEST_F(shell_sort_fixture, sort_array)
{
  algol::algorithms::sort::shell_sort(std::begin(array), std::end(array));
  ASSERT_EQ(array[0], -3);
  ASSERT_EQ(array, sorted_array);
}

TEST_F(shell_sort_fixture, sort_list)
{
  algol::algorithms::sort::shell_sort(std::begin(lst), std::end(lst));
  ASSERT_EQ(lst, sorted_lst);
}

TEST_F(shell_sort_fixture, sort_char)
{
  algol::algorithms::sort::shell_sort(std::begin(x), std::end(x));
  ASSERT_EQ(x, xs);
}

TEST_F(shell_sort_fixture, sort_vec_ciura)
{
  algol::algorithms::sort::shell_sort_ciura_gaps(std::begin(vec), std::end(vec));
  ASSERT_EQ(vec[0], -3);
  ASSERT_EQ(vec, sorted_vec);
}

TEST_F(shell_sort_fixture, sort_string_ciura)
{
  algol::algorithms::sort::shell_sort_ciura_gaps(std::begin(str), std::end(str));
  ASSERT_EQ(str[0], 'A');
  ASSERT_EQ(str, sorted_str);
}

TEST_F(shell_sort_fixture, sort_array_ciura)
{
  algol::algorithms::sort::shell_sort_ciura_gaps(std::begin(array), std::end(array));
  ASSERT_EQ(array[0], -3);
  ASSERT_EQ(array, sorted_array);
}

TEST_F(shell_sort_fixture, sort_list_ciura)
{
  algol::algorithms::sort::shell_sort_ciura_gaps(std::begin(lst), std::end(lst));
  ASSERT_EQ(lst, sorted_lst);
}

TEST_F(shell_sort_fixture, sort_char_ciura)
{
  algol::algorithms::sort::shell_sort_ciura_gaps(std::begin(x), std::end(x));
  ASSERT_EQ(x, xs);
}

TEST_F(shell_sort_fixture, sort_vec_hibbard)
{
  algol::algorithms::sort::shell_sort_hibbard_gaps(std::begin(vec), std::end(vec));
  ASSERT_EQ(vec[0], -3);
  ASSERT_EQ(vec, sorted_vec);
}

TEST_F(shell_sort_fixture, sort_string_hibbard)
{
  algol::algorithms::sort::shell_sort_hibbard_gaps(std::begin(str), std::end(str));
  ASSERT_EQ(str[0], 'A');
  ASSERT_EQ(str, sorted_str);
}

TEST_F(shell_sort_fixture, sort_array_hibbard)
{
  algol::algorithms::sort::shell_sort_hibbard_gaps(std::begin(array), std::end(array));
  ASSERT_EQ(array[0], -3);
  ASSERT_EQ(array, sorted_array);
}

TEST_F(shell_sort_fixture, sort_list_hibbard)
{
  algol::algorithms::sort::shell_sort_hibbard_gaps(std::begin(lst), std::end(lst));
  ASSERT_EQ(lst, sorted_lst);
}

TEST_F(shell_sort_fixture, sort_char_hibbard)
{
  algol::algorithms::sort::shell_sort_hibbard_gaps(std::begin(x), std::end(x));
  ASSERT_EQ(x, xs);
}

TEST_F(shell_sort_fixture, sort_vec_sedgewick)
{
  algol::algorithms::sort::shell_sort_sedgewick_gaps(std::begin(vec), std::end(vec));
  ASSERT_EQ(vec[0], -3);
  ASSERT_EQ(vec, sorted_vec);
}

TEST_F(shell_sort_fixture, sort_string_sedgewick)
{
  algol::algorithms::sort::shell_sort_sedgewick_gaps(std::begin(str), std::end(str));
  ASSERT_EQ(str[0], 'A');
  ASSERT_EQ(str, sorted_str);
}

TEST_F(shell_sort_fixture, sort_array_sedgewick)
{
  algol::algorithms::sort::shell_sort_sedgewick_gaps(std::begin(array), std::end(array));
  ASSERT_EQ(array[0], -3);
  ASSERT_EQ(array, sorted_array);
}

TEST_F(shell_sort_fixture, sort_list_sedgewick)
{
  algol::algorithms::sort::shell_sort_sedgewick_gaps(std::begin(lst), std::end(lst));
  ASSERT_EQ(lst, sorted_lst);
}

TEST_F(shell_sort_fixture, sort_char_sedgewick)
{
  algol::algorithms::sort::shell_sort_sedgewick_gaps(std::begin(x), std::end(x));
  ASSERT_EQ(x, xs);
}
