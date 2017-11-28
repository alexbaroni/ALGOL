#ifndef ALGOL_ALGORITHMS_SHUFFLE_FISHER_YATES_HPP
#define ALGOL_ALGORITHMS_SHUFFLE_FISHER_YATES_HPP

#include <iterator>
#include <random>
#include "stl2/concepts.hpp"

namespace algol::algorithms::shuffle {
  namespace concepts = std::experimental::ranges;

  /**
   * \brief generate a ramdom permutation
   * \details use Fisher-Yates algorithm
   * It generates every n! permutation with uniform probability
   * see https://danluu.com/sattolo/
   * \complexity O(N)
   * \precondition last should be reachable from first otherwise undefined behavior
   * \postcondition range [first, last) contains a permutation of [first, last)
   * \tparam ForwardIt iterator type for [first, last) range
   * \tparam URBG uniform random bits generator type for generating random index
   * \param first iterator to the first element of the range
   * \param last iterator to the one past last element of the range
   * \param gen random number generator
   */
  template <concepts::ForwardIterator ForwardIt, typename URBG>
  void fisher_yates_shuffle (ForwardIt first, ForwardIt last, URBG&& gen)
  {
    using difference_type = typename std::iterator_traits<ForwardIt>::difference_type;

    auto n = std::distance(first, last);
    if (n < 2)
      return;

    auto end = std::prev(last);
    for (auto it = first; it != end; ++it) {
      std::uniform_int_distribution<difference_type> distribution(std::distance(first, it), n - 1);
      std::iter_swap(it, std::next(first, distribution(gen)));
    }
  }
}

#endif //ALGOL_ALGORITHMS_SHUFFLE_FISHER_YATES_HPP
