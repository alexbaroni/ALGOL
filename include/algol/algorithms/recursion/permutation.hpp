#ifndef ALGOL_ALGORITHMS_RECURSION_PERMUTATION_HPP
#define ALGOL_ALGORITHMS_RECURSION_PERMUTATION_HPP

#include <array>
#include <string>
#include <functional>
#include <algorithm>
#include "stl2/concepts.hpp"
#include <boost/coroutine2/all.hpp>

namespace algol::algorithms::recursion {
  namespace concepts = std::experimental::ranges;

  template<typename T>
  using pull_type = typename boost::coroutines2::coroutine<T>::pull_type;

  template<typename T>
  using push_type = typename boost::coroutines2::coroutine<T>::push_type;

  namespace detail {
    template <concepts::Iterator It>
    class iterator_range {
    public:
      iterator_range (It begin, It end) : begin_(begin), end_(end)
      {}

      It begin ()
      { return begin_; }

      It end ()
      { return end_; }

    private:
      It begin_;
      It end_;
    };

    /**
     * \brief generates the n! permutations of [first, last) range one at time
     * \details it uses coroutines to generate a permutation at time
     * \complexity O(N!)
     * \precondition first >= last
     * \postcondition every permutation of the range [first, last) is generated
     * \tparam ForwardIt iterator type for [first, last) range
     * \param sink computed permutation
     * \param begin iterator to the first element of the whole range
     * \param first iterator to the first element of the recursive range
     * \param last iterator to the one past last element of the range
     */
    template <concepts::ForwardIterator ForwardIt>
    void permute (push_type<iterator_range<ForwardIt>>& sink, ForwardIt begin, ForwardIt first, ForwardIt last)
    {
      using namespace std::literals::string_literals;

      if (first > last)
        throw std::domain_error{"the range [first, last) is invalid"s};

      if (first == last) {
        sink(iterator_range(begin, last));
        return;
      }
      for (auto it = first; it != last; ++it) {
        std::iter_swap(first, it);
        permute(sink, begin, std::next(first), last);
        std::iter_swap(first, it);
      }
    }
  }

  /**
   * \brief generates every n! permutation of the n elements of the range
   * \details iterate over every permutation of [first, last) range
   * \complexity O(N!)
   * \precondition first >= last
   * \postcondition every permutation of the range [first, last) is generated
   * \tparam ForwardIt iterator type for [first, last) range
   * \param first iterator to the first element of the range
   * \param last iterator to the one past last element of the range
   * \return a range of iterator that define a permutation
   */
  template<concepts::ForwardIterator ForwardIt>
  pull_type<detail::iterator_range<ForwardIt>> permutations(ForwardIt first, ForwardIt last)
  {
    using std::placeholders::_1;
    pull_type<detail::iterator_range<ForwardIt>> source {std::bind(detail::permute<ForwardIt>, _1, first, first, last)};
    return source;
  }
}

#endif //ALGOL_ALGORITHMS_RECURSION_PERMUTATION_HPP
