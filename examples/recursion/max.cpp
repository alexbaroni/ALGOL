#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <array>
#include <string>
#include <cassert>
#include "stl2/concepts.hpp"
#include <algol/perf/operation_counter.hpp>

namespace concepts = std::experimental::ranges;
using operation_counter = algol::perf::operation_counter<int, std::uint64_t>;

/**
 * \brief find the maximum element of a range
 * \note referncial transparent function
 * \complexity O(N)
 * recurrence relation : T(1) = 1, T(N) = 2T(n/2) + 1 => 2n - 1 (+1 is for < operations)
 * maximun depth of recursion = lg(N)  O(lg(N))
 * \precondition first < last
 * \throws std::domain_error if first >= last
 * \tparam It the type of iterator
 * \param first the first element of the range
 * \param last one past the last element of the range
 * \return the maximum element of the range
 */
template<concepts::RandomAccessIterator It>
requires concepts::CopyConstructible<typename std::iterator_traits<It>::value_type> &&
  concepts::StrictTotallyOrdered<typename std::iterator_traits<It>::value_type>
constexpr auto max (It first, It last)
{
  using namespace std::literals::string_literals;
//TODO: reinsert as soon as bug in stdlib is fixed
//auto count = std::distance(first, last);
  auto count = last - first;
  if (count <= 0)
    throw std::domain_error{"max is undefined on empty range"s};
  if (count == 1) return (*first * 1); // *1 to count recursion operations
  auto mid = first + (last - first) / 2;
  return std::max(max(first, mid), max(mid, last));
}

int main()
{
  constexpr std::array<int, 4> vs{1,6,8,3};
  constexpr auto max_of_vs = max(std::cbegin(vs), std::cend(vs));
  static_assert(max_of_vs == 8);
  assert(max_of_vs == 8);
  std::cout << max_of_vs << std::endl;
  std::array<int, 5> xs{1,9,8,3,6};
  auto max_of_xs = max(std::begin(xs), std::end(xs));
  assert(max_of_xs == 9);
  std::cout << max_of_xs << std::endl;

  std::array<operation_counter,8> ys{1,6,8,3,7,9,2,5};
  auto max_of_ys = max(std::cbegin(ys), std::cend(ys));

  std::cout << "recursion times " << operation_counter::multiplications()
            << " compares " << operation_counter::less_comparisons() << std::endl;

  //constexpr std::array<int, 0> zs{};
  //constexpr auto max_of_zs = max(std::begin(zs), std::end(zs)); // compiler error
  //assert(max_of_zs == 0);
  //std::array<int, 0> zs{};
  //auto max_of_zs = max(std::begin(zs), std::end(zs)); // throws at runtime
  //assert(max_of_zs == 0);
}
