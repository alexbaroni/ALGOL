#ifndef ALGOL_ALGORITHMS_SORT_BOGO_SORT_HPP
#define ALGOL_ALGORITHMS_SORT_BOGO_SORT_HPP

#include <algorithm>
#include <iterator>
#include <random>
#include "stl2/concepts.hpp"
#include "algol/algorithms/shuffle/fisher_yates.hpp"
#include "algol/algorithms/recursion/permutation.hpp"

namespace algol::algorithms::sort {

  namespace concepts = std::experimental::ranges;

  /**
   * \brief random bogo sort
   * \details uses Fisher-Yates shuffle to generate random permutations
   * \complexity O(N*N!)
   * \precondition last should be reachable from first otherwise undefined behavior
   * \postcondition range [first, last) is sorted according to Comp
   * \tparam ForwardIt iterator type for [first, last) range
   * \tparam Compare comparison type
   * \param first iterator to the first element of the range
   * \param last iterator to the one past last element of the range
   * \param comp comparison invokable
   */
  template <concepts::ForwardIterator ForwardIt,
      typename Compare = std::less<typename std::iterator_traits<ForwardIt>::value_type>>
  void bogo_sort_random (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    using namespace algol::algorithms::shuffle;

    if (std::distance(first, last) < 2)
      return;

    std::random_device rd;
    std::mt19937 gen(rd());

    while (!std::is_sorted(first, last, comp)) {
      fisher_yates_shuffle(first, last, gen);
    }
  }

  /**
   * \brief deterministic bogo sort
   * \complexity O(N*N!)
   * \precondition last should be reachable from first otherwise undefined behavior
   * \postcondition range [first, last) is sorted according to Comp
   * \tparam ForwardIt iterator type for [first, last) range
   * \tparam Compare comparison type
   * \param first iterator to the first element of the range
   * \param last iterator to the one past last element of the range
   * \param comp comparison invokable
   */
  template <concepts::ForwardIterator ForwardIt,
      typename Compare = std::less<typename std::iterator_traits<ForwardIt>::value_type>>
  void bogo_sort_deterministic (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    using namespace algol::algorithms::recursion;

    if (std::distance(first, last) < 2)
      return;

    for (auto vs : permutations(first, last)) {
      if (std::is_sorted(std::begin(vs), std::end(vs), comp)) {
        break;
      }
    }
  }
}

#endif //ALGOL_ALGORITHMS_SORT_BOGO_SORT_HPP
