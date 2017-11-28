#ifndef ALGOL_EXAMPLES_UTILITY_HPP
#define ALGOL_EXAMPLES_UTILITY_HPP

#include <numeric>
#include <algorithm>
#include <algol/algorithms/algorithm.hpp>

template <typename T>
struct test_convertible_to_numeric_udt {
  using value_type = T;

  test_convertible_to_numeric_udt (T i) : value_(i)
  {}

  test_convertible_to_numeric_udt (test_convertible_to_numeric_udt const& value) : value_ {value.value_}
  {}

  operator T ()
  { return value_; }

private:
  // generates a non-template operator... for this T and this Counter
  template <typename U>
  friend bool operator== (U const& y, test_convertible_to_numeric_udt const& x)
  {
    return T(y) == x.value_;
  }

  template <typename U>
  friend bool operator== (test_convertible_to_numeric_udt const& x, U const& y)
  {
    return x.value_ == T(y);
  }

  friend bool operator== (test_convertible_to_numeric_udt const& x, test_convertible_to_numeric_udt const& y)
  {
    return x.value_ == y.value_;
  }

  template <typename U>
  friend bool operator!= (U const& y, test_convertible_to_numeric_udt const& x)
  {
    return T(y) != x.value_;
  }

  template <typename U>
  friend bool operator!= (test_convertible_to_numeric_udt const& x, U const& y)
  {
    return x.value_ != T(y);
  }

  friend bool operator!= (test_convertible_to_numeric_udt const& x, test_convertible_to_numeric_udt const& y)
  {
    return x.value_ != y.value_;
  }

  template <typename U>
  friend bool operator< (U const& y, test_convertible_to_numeric_udt const& x)
  {
    return T(y) < x.value_;
  }

  template <typename U>
  friend bool operator< (test_convertible_to_numeric_udt const& x, U const& y)
  {
    return x.value_ < T(y);
  }

  friend bool operator< (test_convertible_to_numeric_udt const& x, test_convertible_to_numeric_udt const& y)
  {
    return x.value_ < y.value_;
  }

  template <typename U>
  friend bool operator> (U const& y, test_convertible_to_numeric_udt const& x)
  {
    return T(y) > x.value_;
  }

  template <typename U>
  friend bool operator> (test_convertible_to_numeric_udt const& x, U const& y)
  {
    return x.value_ > T(y);
  }

  friend bool operator> (test_convertible_to_numeric_udt const& x, test_convertible_to_numeric_udt const& y)
  {
    return x.value_ > y.value_;
  }

  template <typename U>
  friend bool operator<= (U const& y, test_convertible_to_numeric_udt const& x)
  {
    return T(y) <= x.value_;
  }

  template <typename U>
  friend bool operator<= (test_convertible_to_numeric_udt const& x, U const& y)
  {
    return x.value_ <= T(y);
  }

  friend bool operator<= (test_convertible_to_numeric_udt const& x, test_convertible_to_numeric_udt const& y)
  {
    return x.value_ <= y.value_;
  }

  template <typename U>
  friend bool operator>= (U const& y, test_convertible_to_numeric_udt const& x)
  {
    return T(y) >= x.value_;
  }

  template <typename U>
  friend bool operator>= (test_convertible_to_numeric_udt const& x, U const& y)
  {
    return x.value_ >= T(y);
  }

  friend bool operator>= (test_convertible_to_numeric_udt const& x, test_convertible_to_numeric_udt const& y)
  {
    return x.value_ >= y.value_;
  }

  T value_;
};

template <typename T>
struct test_numeric_udt {
  using value_type = T;

  test_numeric_udt (T i) : value_(i)
  {}

  test_numeric_udt (test_numeric_udt const& value) : value_ {value.value_}
  {}

  test_numeric_udt operator+ (test_numeric_udt const& x)
  { return test_numeric_udt{value_ + x.value_}; }

  test_numeric_udt operator- (test_numeric_udt const& x)
  { return test_numeric_udt{value_ - x.value_}; }

  test_numeric_udt operator* (test_numeric_udt const& x)
  { return test_numeric_udt{value_ * x.value_}; }

  test_numeric_udt operator/ (test_numeric_udt const& x)
  { return test_numeric_udt{value_ / x.value_}; }

  T const& value () const
  { return value_; }

private:

  // generates a non-template operator... for this T and this Counter
  template <typename U>
  friend bool operator== (U const& y, test_numeric_udt const& x)
  {
    return T(y) == x.value_;
  }

  template <typename U>
  friend bool operator== (test_numeric_udt const& x, U const& y)
  {
    return x.value_ == T(y);
  }

  friend bool operator== (test_numeric_udt const& x, test_numeric_udt const& y)
  {
    return x.value_ == y.value_;
  }

  template <typename U>
  friend bool operator!= (U const& y, test_numeric_udt const& x)
  {
    return T(y) != x.value_;
  }

  template <typename U>
  friend bool operator!= (test_numeric_udt const& x, U const& y)
  {
    return x.value_ != T(y);
  }

  friend bool operator!= (test_numeric_udt const& x, test_numeric_udt const& y)
  {
    return x.value_ != y.value_;
  }

  template <typename U>
  friend bool operator< (U const& y, test_numeric_udt const& x)
  {
    return T(y) < x.value_;
  }

  template <typename U>
  friend bool operator< (test_numeric_udt const& x, U const& y)
  {
    return x.value_ < T(y);
  }

  friend bool operator< (test_numeric_udt const& x, test_numeric_udt const& y)
  {
    return x.value_ < y.value_;
  }

  template <typename U>
  friend bool operator> (U const& y, test_numeric_udt const& x)
  {
    return T(y) > x.value_;
  }

  template <typename U>
  friend bool operator> (test_numeric_udt const& x, U const& y)
  {
    return x.value_ > T(y);
  }

  friend bool operator> (test_numeric_udt const& x, test_numeric_udt const& y)
  {
    return x.value_ > y.value_;
  }

  template <typename U>
  friend bool operator<= (U const& y, test_numeric_udt const& x)
  {
    return T(y) <= x.value_;
  }

  template <typename U>
  friend bool operator<= (test_numeric_udt const& x, U const& y)
  {
    return x.value_ <= T(y);
  }

  friend bool operator<= (test_numeric_udt const& x, test_numeric_udt const& y)
  {
    return x.value_ <= y.value_;
  }

  template <typename U>
  friend bool operator>= (U const& y, test_numeric_udt const& x)
  {
    return T(y) >= x.value_;
  }

  template <typename U>
  friend bool operator>= (test_numeric_udt const& x, U const& y)
  {
    return x.value_ >= T(y);
  }

  friend bool operator>= (test_numeric_udt const& x, test_numeric_udt const& y)
  {
    return x.value_ >= y.value_;
  }

  T value_;
};

template <typename ForwardIt, typename V = typename std::iterator_traits<ForwardIt>::value_type>
void build_sorted_range (ForwardIt first, ForwardIt last, V value)
{
  std::iota(first, last, value);
}

template <typename ForwardIt, typename V = typename std::iterator_traits<ForwardIt>::value_type>
void build_mostly_sorted_range (ForwardIt first, ForwardIt last, V value)
{
  build_sorted_range(first, last, value);
  auto n = std::distance(first, last);
  if (n < 5)
    return;

  for (auto i = 0; i < 2; ++i)
    std::iter_swap(first + (n / 2) - i, first + n / 2 + i + 1);
}

template <typename ForwardIt, typename V = typename std::iterator_traits<ForwardIt>::value_type>
void build_reverse_sorted_range (ForwardIt first, ForwardIt last, V value)
{
  std::iota(first, last, value);
  std::reverse(first, last);
}

template <typename ForwardIt, typename V = typename std::iterator_traits<ForwardIt>::value_type>
void build_mostly_reverse_sorted_range (ForwardIt first, ForwardIt last, V value)
{
  build_reverse_sorted_range(first, last, value);
  auto n = std::distance(first, last);
  if (n < 5)
    return;

  for (auto i = 0; i < 2; ++i)
    std::iter_swap(first + (n / 2) - i, first + n / 2 + i + 1);
}

template <typename ForwardIt, typename URBG, typename V = typename std::iterator_traits<ForwardIt>::value_type>
void build_unsorted_range (ForwardIt first, ForwardIt last, V min, V max, URBG&& gen)
{
  std::uniform_int_distribution<V> distribution(min, max);
  for (auto it = first; it != last; ++it)
    *it = distribution(gen);
}

#endif //ALGOL_EXAMPLES_UTILITY_HPP
