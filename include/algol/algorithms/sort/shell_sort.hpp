#ifndef ALGOL_ALGORITHMS_SORT_SHELL_SORT_HPP
#define ALGOL_ALGORITHMS_SORT_SHELL_SORT_HPP

#include <iterator>
#include "stl2/concepts.hpp"
#include "algol/sequence/generator/halving_generator.hpp"
#include "algol/sequence/generator/ciura_gap_sequence_generator.hpp"
#include "algol/sequence/generator/hibbard_gap_sequence_generator.hpp"
#include "algol/sequence/generator/sedgewick_gap_sequence_generator.hpp"

namespace algol::algorithms::sort {

  namespace concepts = std::experimental::ranges;

  namespace detail {
    template <concepts::ForwardIterator ForwardIt, typename GapSequence, typename Compare>
    void shell_sort (ForwardIt first, ForwardIt last, GapSequence gap_seq, Compare comp)
    {
      auto n = std::distance(first, last);
      if (n < 2)
        return;

      for (auto&& gap : gap_seq) {
        for (auto next = std::next(first, gap); next != last; ++next) {
          auto value = next;
          auto prev = std::next(first, std::distance(first, next) - gap);
          while (std::distance(first, value) >= gap && comp(*value, *prev)) {
            std::iter_swap(value, prev);
            value = prev;
            n = std::distance(first, value);
            prev = std::next(first, n > gap ? n - gap : 0);
          }
        }
      }
    }

    template <concepts::BidirectionalIterator BidirIt, typename GapSequence, typename Compare>
    void shell_sort (BidirIt first, BidirIt last, GapSequence gap_seq, Compare comp)
    {
      auto n = std::distance(first, last);
      if (n < 2)
        return;

      for (auto&& gap : gap_seq) {
        for (auto next = std::next(first, gap); next != last; ++next) {
          auto value = next;
          while (std::distance(first, value) >= gap && comp(*value, *std::prev(value, gap))) {
            std::iter_swap(value, std::prev(value, gap));
            value = std::prev(value, gap);
          }
        }
      }
    }
  }

  template <concepts::ForwardIterator ForwardIt,
      typename Compare = std::less<typename std::iterator_traits<ForwardIt>::value_type>>
  void shell_sort (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    using halving_seq = algol::sequence::halving_seq<typename std::iterator_traits<ForwardIt>::difference_type>;
    detail::shell_sort(first, last, halving_seq{std::distance(first, last)}, comp);
  }

  template <concepts::ForwardIterator ForwardIt,
      typename Compare = std::less<typename std::iterator_traits<ForwardIt>::value_type>>
  void shell_sort_ciura_gaps (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    using ciura_gap_seq = algol::sequence::ciura_gap_seq<typename std::iterator_traits<ForwardIt>::difference_type>;
    detail::shell_sort(first, last, ciura_gap_seq{std::distance(first, last)}, comp);
  }

  template <concepts::ForwardIterator ForwardIt,
      typename Compare = std::less<typename std::iterator_traits<ForwardIt>::value_type>>
  void shell_sort_hibbard_gaps (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    using hibbard_gap_seq = algol::sequence::hibbard_gap_seq<typename std::iterator_traits<ForwardIt>::difference_type>;
    detail::shell_sort(first, last, hibbard_gap_seq{std::distance(first, last)}, comp);
  }

  template <concepts::ForwardIterator ForwardIt,
      typename Compare = std::less<typename std::iterator_traits<ForwardIt>::value_type>>
  void shell_sort_sedgewick_gaps (ForwardIt first, ForwardIt last, Compare comp = Compare{})
  {
    using sedgewick_gap_seq = algol::sequence::sedgewick_gap_seq<typename std::iterator_traits<ForwardIt>::difference_type>;
    detail::shell_sort(first, last, sedgewick_gap_seq{std::distance(first, last)}, comp);
  }

  template <concepts::BidirectionalIterator BidirIt,
      typename Compare = std::less<typename std::iterator_traits<BidirIt>::value_type>>
  void shell_sort (BidirIt first, BidirIt last, Compare comp = Compare{})
  {
    using halving_seq = algol::sequence::halving_seq<typename std::iterator_traits<BidirIt>::difference_type>;
    detail::shell_sort(first, last, halving_seq{std::distance(first, last)}, comp);
  }

  template <concepts::BidirectionalIterator BidirIt,
      typename Compare = std::less<typename std::iterator_traits<BidirIt>::value_type>>
  void shell_sort_ciura_gaps (BidirIt first, BidirIt last, Compare comp = Compare{})
  {
    using ciura_gap_seq = algol::sequence::ciura_gap_seq<typename std::iterator_traits<BidirIt>::difference_type>;
    detail::shell_sort(first, last, ciura_gap_seq{std::distance(first, last)}, comp);
  }

  template <concepts::BidirectionalIterator BidirIt,
      typename Compare = std::less<typename std::iterator_traits<BidirIt>::value_type>>
  void shell_sort_hibbard_gaps (BidirIt first, BidirIt last, Compare comp = Compare{})
  {
    using hibbard_gap_seq = algol::sequence::hibbard_gap_seq<typename std::iterator_traits<BidirIt>::difference_type>;
    detail::shell_sort(first, last, hibbard_gap_seq{std::distance(first, last)}, comp);
  }

  template <concepts::BidirectionalIterator BidirIt,
      typename Compare = std::less<typename std::iterator_traits<BidirIt>::value_type>>
  void shell_sort_sedgewick_gaps (BidirIt first, BidirIt last, Compare comp = Compare{})
  {
    using sedgewick_gap_seq = algol::sequence::sedgewick_gap_seq<typename std::iterator_traits<BidirIt>::difference_type>;
    detail::shell_sort(first, last, sedgewick_gap_seq{std::distance(first, last)}, comp);
  }
}

#endif //ALGOL_ALGORITHMS_SORT_SHELL_SORT_HPP
