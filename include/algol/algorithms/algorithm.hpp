#ifndef ALGOL_ALGORITHM_HPP
#define ALGOL_ALGORITHM_HPP

#include "stl2/concepts.hpp"

namespace algol::algorithms {
  namespace concepts = std::experimental::ranges;

  template <concepts::Swappable T>
  constexpr void swap (T& rhs, T& lhs)
  {
    T tmp {std::move(rhs)};
    rhs = std::move(lhs);
    lhs = std::move(tmp);
  }

  template <concepts::BidirectionalIterator BidirIt>
  constexpr void reverse (BidirIt first, BidirIt last)
  {
    while ((first != last) && (first != --last)) {
      swap(*first++, *last);
    }
  }

  //TODO: reinsert std::distance as soon as bug in stdlib is fixed
  //template<concepts::ForwardIterator ForwardIt>
  //constexpr ForwardIt rotate(ForwardIt first, ForwardIt middle, ForwardIt last)

  template <concepts::RandomAccessIterator RandomIt>
  requires concepts::CopyConstructible<typename std::iterator_traits<RandomIt>::value_type>
  constexpr RandomIt rotate(RandomIt
  first,
  RandomIt middle, RandomIt
  last) {
  //TODO: reinsert std::distance as soon as bug in stdlib is fixed
  //auto n = std::distance(middle, last);
  auto n = last - middle;
  //TODO: reinsert std::distance as soon as bug in stdlib is fixed
  //if (n < 1 || std::distance(first, middle) < 1)
  if (n < 1 || (middle - first) < 1)
  return
  first;

  auto d = n;
  for (
  auto it = first;
  it !=
  middle;
  ++it) {
  swap(* it, * middle
  );
  if (d > 1) {
  --
  d;
  ++
  middle;
}
}
//TODO: reinsert std::advance as soon as bug in stdlib is fixed
//return std::next(first, n);
return first +
n;
}
}

#endif //ALGOL_ALGORITHM_HPP
