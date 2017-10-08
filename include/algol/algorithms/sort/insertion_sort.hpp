/**
 * \brief insertion sort implementations
 * \details insertion sort is quadartic running time complexity sort algorithm
 * From Wikipedia
 * Insertion sort is a simple sorting algorithm that builds the final sorted array (or list) one item at a time.
 * It is much less efficient on large lists than more advanced algorithms such as quicksort, heapsort, or merge sort.
 * The algorithm divides the input list into two parts: the sublist of items partially sorted,
 * which is built up from left to right at the front (left) of the list,
 * and the sublist of items remaining to be sorted that occupy the rest of the list.
 * Initially, the partially sorted sublist is empty and the unsorted sublist is the entire input list.
 * The algorithm proceeds by inserting the first unsorted element in the unsorted sublist,
 * in the correct position in the partially sorted list.
 * Insertion sort is very similar to selection sort. As in selection sort, after k passes through the array,
 * the first k elements are in sorted order. For selection sort these are the k smallest elements,
 * while in insertion sort they are whatever the first k elements were in the unsorted array.
 * Insertion sort's advantage is that it only scans as many elements as needed to determine the correct location
 * of the k+1st element, while selection sort must scan all remaining elements to find the absolute smallest element.
 * Assuming the k+1st element's rank is random, insertion sort will on average require shifting
 * half of the previous k elements, while selection sort always requires scanning all unplaced elements.
 * So for unsorted input, insertion sort will usually perform about half as many comparisons as selection sort.
 * If the input array is reverse-sorted, insertion sort performs as many comparisons as selection sort.
 * If the input array is already sorted, insertion sort performs as few as n-1 comparisons,
 * thus making insertion sort more efficient when given sorted or "nearly sorted" arrays.
 * While insertion sort typically makes fewer comparisons than selection sort, it requires more writes
 * because the inner loop can require shifting large sections of the sorted portion of the array.
 * In general, insertion sort will write to the array O(n^2) times, whereas selection sort will write
 * only O(n) times. For this reason selection sort may be preferable in cases where writing
 * to memory is significantly more expensive than reading, such as with EEPROM or flash memory.
 * It is in-place stable and adaptive sorting algorithm
 */
#ifndef ALGOL_ALGORITHMS_SORT_INSERTION_SORT_HPP
#define ALGOL_ALGORITHMS_SORT_INSERTION_SORT_HPP

#include <iterator>
#include "stl2/concepts.hpp"

namespace algol::algorithms::sort {

  namespace concepts = std::experimental::ranges;

  /**
   * \brief insertion sort for bidirectional iterator
   * \details it inserts the first unsorted element in the correct position in the partially sorted range.
   * \complexity O(N^2) comparison, O(N^2) swaps; worst, average and O(N) comparison O(1) swaps; best case.
   * \precondition last should be reachable from first otherwise undefined behavior
   * \postcondition range [first, last) is sorted according to Comp
   * \tparam BidirIt iterator type for [first, last) range
   * \tparam Compare comparison type
   * \param first iterator to the first element of the range
   * \param last iterator to the one past last element of the range
   * \param comp comparison invokable
   */

  template<concepts::BidirectionalIterator BidirIt,
      typename Compare = std::less<typename std::iterator_traits<BidirIt>::value_type>>
  void standard_insertion_sort (BidirIt first, BidirIt last, Compare comp = Compare{})
  {
    if (std::distance(first, last) < 2)
      return;

    for (auto unsorted = std::next(first); unsorted != last; ++unsorted) {
      for(auto it = unsorted; it != first && comp(*it, *std::prev(it)); --it) {
        std::iter_swap(it, std::prev(it));
      }
    }
  }

  /**
   * \brief insertion sort for forward iterator using STL algorithms
   * \details it inserts the first unsorted element in the correct position in the partially sorted range.
   * \note idea from https://stackoverflow.com/questions/18453945/c-generic-insertion-sort
   * \complexity O(N^2) comparison, O(N^2) swaps; worst, average and O(N) comparison O(1) swaps; best case.
   * \precondition last should be reachable from first otherwise undefined behavior
   * \postcondition range [first, last) is sorted according to Comp
   * \tparam ForwardIt iterator type for [first, last) range
   * \tparam Compare comparison type
   * \param first iterator to the first element of the range
   * \param last iterator to the one past last element of the range
   * \param comp comparison invokable
   */
  template<concepts::ForwardIterator ForwardIt,
      typename Compare = std::less<typename std::iterator_traits<ForwardIt>::value_type>>
  void stl_insertion_sort(ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    if (std::distance(first, last) < 2)
      return;
    // upper_bound finds with logarithmic complexity the first element, in the partially sorted range,
    // that is greater than first unsorted element.
    // rotate make room for that element shifting the elements that are greater than it and put it in the correct
    // position eg:
    // 1 2 6 8 5 9 10: 5 is the first unsorted element, upper_bound return iterator pointing to 6
    // rotate works on 6 8 5 elements and the result of the call is 5 6 8.
    // this makes room for 5 and shifts 6 and 8.
    for (auto it = first; it != last; ++it)
      std::rotate(std::upper_bound(first, it, *it, comp), it, std::next(it));
  }

  /**
   * \brief insertion sort for forward iterator
   * \details it inserts the first unsorted element in the correct position in the partially sorted range.
   * \note it is a bit slower than STL version because of std::rotate optimization for iterator type
   * \complexity O(N^2) comparison, O(N^2) swaps; worst, average and O(N) comparison O(1) swaps; best case.
   * \precondition last should be reachable from first otherwise undefined behavior
   * \postcondition range [first, last) is sorted according to Comp
   * \tparam ForwardIt iterator type for [first, last) range
   * \tparam Compare comparison type
   * \param first iterator to the first element of the range
   * \param last iterator to the one past last element of the range
   * \param comp comparison invokable
   */
  template<concepts::ForwardIterator ForwardIt,
      typename Compare = std::less<typename std::iterator_traits<ForwardIt>::value_type>>
  void insertion_sort(ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    if (std::distance(first, last) < 2)
      return;
    for (auto it = std::next(first); it != last; ++it) {
      // finds in the [first, it) range the insertion point for the first unsorted element
      auto rot_it = first;
      // linear upper_bound
      // while (!comp(*it, *rot_it) && rot_it != it)
      //   ++rot_it;
      // logarithmic upper_bound
      auto count = std::distance(rot_it, it);
      while (count > 0) {
        auto middle = rot_it;
        auto step = count / 2;
        std::advance(middle, step);
        if (!comp(*it, *middle)) {
          rot_it = ++middle;
          count -= step + 1;
        }
        else
          count = step;
      }
      // make a rotation to place the first unsorted element in place (partially sorted)
      while(rot_it != it) {
        std::iter_swap(rot_it, it);
        ++rot_it;
      }
    }
  }
}

#endif //ALGOL_ALGORITHMS_SORT_INSERTION_SORT_HPP
