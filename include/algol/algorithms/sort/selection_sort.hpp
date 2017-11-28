/**
 * \brief selection sort implementations
 * \details selection sort is quadartic running time complexity sort algorithm
 * From Wikipedia
 * The algorithm divides the input list into two parts: the sublist of items already sorted,
 * which is built up from left to right at the front (left) of the list,
 * and the sublist of items remaining to be sorted that occupy the rest of the list.
 * Initially, the sorted sublist is empty and the unsorted sublist is the entire input list.
 * The algorithm proceeds by finding the smallest (or largest, depending on sorting order) element
 * in the unsorted sublist, exchanging (swapping) it with the leftmost unsorted element (putting it in sorted order),
 * and moving the sublist boundaries one element to the right.
 * and repeating the pass through the list until no swaps are done.
 * It is in-place not stable and not adaptive sorting algorithm
 */
#ifndef ALGOL_ALGORITHMS_SORT_SELECTION_SORT_HPP
#define ALGOL_ALGORITHMS_SORT_SELECTION_SORT_HPP

#include <iterator>
#include "stl2/concepts.hpp"

namespace algol::algorithms::sort {

  namespace concepts = std::experimental::ranges;

  template <concepts::ForwardIterator ForwardIt,
      typename Compare = std::less<typename std::iterator_traits<ForwardIt>::value_type>>
  void selection_sort_stl (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    for (auto it = first; it != last; ++it)
      std::iter_swap(it, std::min_element(it, last, comp));
  }

  /**
   * \brief selection sort
   * \details it repeats a linear search to find the smallest element and puts it correct position.
   * \complexity O(N^2) comparison, O(N) swaps; worst, average and best case.
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
  void selection_sort (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    auto n = std::distance(first, last);
    if (n < 2)
      return;

    while (first != last) {
      // loop invariant (holds also at the end of this loop) the range [old first, last)
      // is a permutation of the input range, old first is the first iterator passed in
      // first ranges from old first to element before last
      // first != old first -> every element in range [old first, first] is sorted
      // first != old first -> every element in range [old first, first] <= every element in range [first+1, last)
      auto smallest = first;
      for (auto unsorted = std::next(first); unsorted != last; ++unsorted) {
        // loop invariant (holds also at the end of this loop)
        // *smallest <= every element in range [first, unsorted)
        // every element in range [old first, first) <= *smallest
        // unsorted in range [first+1, last)
        // smallest in range [first,  unsorted)
        if (comp(*unsorted, *smallest))
          smallest = unsorted;
      }
      // loop postcondition
      // *smallest <= every element in range [first, last)

      // this put the smallest element found in the [first, last) range in sorted position
      // so that one more element is sorted
      if (first != smallest)
        std::iter_swap(first, smallest);
      ++first;
    }
    // loop postcondition
    // the range [old first, last) is a permutation of the input range it has the same elements in sorted order
  }
}

#endif //ALGOL_ALGORITHMS_SORT_SELECTION_SORT_HPP
