/**
 * \brief bubble sort implementations
 * \details bubble sort is quadartic running time complexity sort algorithm
 * Sort by comparing each adjacent pair of items in a list in turn, swapping the items if necessary,
 * and repeating the pass through the list until no swaps are done.
 * It is stable in-place and adaptive sorting algorithm
 * Comb sort is faster than bubble sort and compare elements separated by decreasing gap but it is not stable.
 */
#ifndef ALGOL_ALGORITHMS_SORT_BUBBLE_SORT_HPP
#define ALGOL_ALGORITHMS_SORT_BUBBLE_SORT_HPP

#include <iterator>
#include "stl2/concepts.hpp"

namespace algol::algorithms::sort {

  namespace concepts = std::experimental::ranges;

  /**
   * \brief standard bubble sort
   * \details it compares adjacent pair of elements and swaps them it they are out of order
   * \complexity O(N^2) [O(N) if range is sorted - best case]
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
  void bubble_sort (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    auto n = std::distance(first, last);
    if (n < 2)
      return;

    bool swapped;
    do {
      // loop invariant (holds also at the end of this loop)
      // the range {first, last) is a permutation of the input range and
      // not swapped -> range [first,last) is sorted
      swapped = false;
      for (auto next = std::next(first), prev = first; next != last; ++next, ++prev) {
        // loop invariant (holds also at the end of this loop)
        // next ranges from second to last element
        // prev ranges from first to penultimate element
        // the range {first, last) is a permutation of the input range
        // not swapped -> range [first,next) is sorted
        if (comp(*next, *prev)) {
          std::iter_swap(next, prev);
          swapped = true;
        }
      }
    } while (swapped);
    // loop postcondition
    // the range {first, last) is a permutation of the input range it has the same elements in sorted order
  }

  /**
   * \brief optimized bubble sort
   * \details it compares adjacent pair of elements and swaps them it they are out of order
   * Every iteration the range length is reduced by one element because the last element is in its final position
   * \complexity O(N^2) [O(N) if range is sorted - best case]
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
  void bubble_sort_optimized (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    auto n = std::distance(first, last);
    if (n < 2)
      return;

    bool swapped;
    do {
      // loop invariant (holds also at the end of this loop), old last is the last iterator passed in
      // the range {first, old last) is a permutation of the input range and
      // not swapped -> range [first, old last) is sorted
      // range [last, old last) is sorted
      // last != old last -> every element in range [first, last) <= *last
      swapped = false;
      for (auto next = std::next(first), prev = first; next != last; ++next, ++prev) {
        // loop invariant (holds also at the end of this loop), old last is the last iterator passed in
        // the range [first, old last) is a permutation of the input range
        // next ranges from second to last element
        // prev ranges from first to element before last
        // range [last, old last) is sorted
        // last != old last -> every element in range [first, last) <= *last
        if (comp(*next, *prev)) {
          std::iter_swap(next, prev);
          swapped = true;
        }
      }
      // loop postcondition
      // last != old last -> every element in range [first, last] <= *last
      last = std::next(first, --n);
    } while (swapped);
    // loop postcondition
    // the range {first, old last) is a permutation of the input range it has the same elements in sorted order
  }

  /**
   * \brief fast bubble sort
   * \details it compares adjacent pair of elements and swaps them it they are out of order
   * From wikipedia
   * It can happen that more than one element is placed in their final position on a single pass.
   * In particular, after every pass, all elements after the last swap are sorted,
   * and do not need to be checked again. This allows us to skip over a lot of the elements,
   * resulting in about a worst case 50% improvement in comparison count
   * (though no improvement in swap counts), and adds very little complexity
   * \complexity O(N^2) [O(N) if range is sorted - best case]
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
  void bubble_sort_fast (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    auto n = std::distance(first, last);
    if (n < 2)
      return;

    do {
      // loop invariant (holds also at the end of this loop), old last is the last iterator passed in
      // the range {first, old last) is a permutation of the input range and
      // n == 0 (no swaps) -> range [first, old last) is sorted
      // range [last, old last) is sorted
      // last != old last -> every element in range [first, last) <= *last
      n = 0;
      for (auto next = std::next(first), prev = first; next != last; ++next, ++prev) {
        // loop invariant (holds also at the end of this loop), old last is the last iterator passed in
        // the range [first, old last) is a permutation of the input range
        // last is where last swap was done
        // next ranges from second to last element
        // prev ranges from first to element before last
        // range [last, old last) is sorted
        // last != old last -> every element in range [first, last) <= *last
        if (comp(*next, *prev)) {
          std::iter_swap(next, prev);
          n = std::distance(first, next);
        }
      }
      // loop postcondition
      // last != old last -> every element in range [first, last] <= *last
      last = std::next(first, n);
    } while (n > 0);
    // loop postcondition
    // the range {first, old last) is a permutation of the input range it has the same elements in sorted order
  }

  /**
   * \brief comb sort (bubble sort optimization)
   * \details it compares pair of elements separated by a gap and swaps them it they are out of order
   * From wikipedia
   * The basic idea is to eliminate turtles, or small values near the end of the list,
   * since in a bubble sort these slow the sorting down tremendously.
   * Rabbits, large values around the beginning of the list, do not pose a problem in bubble sort.
   * In bubble sort, when any two elements are compared, they always have a gap (distance from each other) of 1.
   * The basic idea of comb sort is that the gap can be much more than 1.
   * The inner loop of bubble sort, which does the actual swap, is modified such that gap between swapped elements
   * goes down (for each iteration of outer loop) in steps of a "shrink factor" k: [ n/k, n/k^2, n/k^3, ..., 1 ].
   * The gap starts out as the length of the list n being sorted divided by the shrink factor k
   * (generally 1.3) and one pass of the aforementioned modified bubble sort is applied with that gap.
   * Then the gap is divided by the shrink factor again, the list is sorted with this new gap,
   * and the process repeats until the gap is 1. At this point, comb sort continues using a gap of 1
   * until the list is fully sorted. The final stage of the sort is thus equivalent to a bubble sort,
   * but by this time most turtles have been dealt with, so a bubble sort will be efficient.
   * \note it uses the comb sort 11+ see http://cs.clackamas.cc.or.us/molatore/cs260Spr03/combsort.htm
   * \complexity O(N^2) worst case Θ(N*LOG2 N) best case,
   * Ω(N^2/2^p) average case see https://en.wikipedia.org/wiki/Talk%3AComb_sort
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
  void comb_sort (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    auto gap = std::distance(first, last);
    if (gap < 2)
      return;

    bool swapped;
    auto shrink_numerator = 13, shrink_denominator = 10;
    do {
      // loop invariant (holds also at the end of this loop) the range [first, last)
      // is a permutation of the input range and not swapped -> [first, last) is gap_sorted for gap
      // [first, old last) gap_sorted for gap = 1 -> [first, last) is sorted
      // 1 <= gap <= number of elements in [first, last) range
      gap = (gap * shrink_denominator) / shrink_numerator;
      if (gap > 1) {
        if (gap == 9 || gap == 10)
          gap = 11;
      }
      else {
        gap = 1;
      }

      swapped = false;
      for (auto prev = first, next = std::next(prev, gap); next != last; ++prev, ++next) {
        // loop invariant (holds also at the end of this loop) the range [first, last)
        // is a permutation of the input range
        // 1 <= gap <= number of elements in [first, last) range
        // next ranges from first+gap to last element
        // prev ranges from first to last - gap
        // not swapped -> [first, next] is gap_sorted for gap
        if (comp(*next, *prev)) {
          std::iter_swap(next, prev);
          swapped = true;
        }
      }
    } while (gap > 1 || swapped);
    // loop postcondition
    // the range {first, old last) is a permutation of the input range it has the same elements in sorted order
  }
}

#endif //ALGOL_ALGORITHMS_SORT_BUBBLE_SORT_HPP
