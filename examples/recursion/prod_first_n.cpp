#include <iostream>
#include <iterator>
#include <array>
#include "stl2/concepts.hpp"

namespace concepts = std::experimental::ranges;

template<concepts::InputIterator It>
auto product_of_first_n_elements(It first, std::size_t n)
{
  if (n == 0) return 1;
  return *first * product_of_first_n_elements(std::next(first), n - 1);
}

template<concepts::InputIterator It>
auto product(It first, It last)
{
  if (first == last) return 1;
  return *first * product(std::next(first), last);
}

int main()
{
  std::array<int, 10> vs{5,6,2,8,1,7,3,4,9,1};
  std::cout << product_of_first_n_elements(std::begin(vs), 4) << std::endl;
  std::cout << product_of_first_n_elements(std::begin(vs) + 2, 5) << std::endl;
  std::cout << product(std::begin(vs), std::begin(vs) + 4) << std::endl;
  std::cout << product(std::begin(vs) + 2, std::begin(vs) + 7) << std::endl;
}
