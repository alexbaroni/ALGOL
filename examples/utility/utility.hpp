#ifndef ALGOL_EXAMPLES_UTILITY_HPP
#define ALGOL_EXAMPLES_UTILITY_HPP

template<typename T>
struct test_convertible_to_numeric_udt {
  using value_type = T;
  test_convertible_to_numeric_udt(T i) : value_(i) {}
  test_convertible_to_numeric_udt (test_convertible_to_numeric_udt const& value) : value_ {value.value_}
  {}
  operator T ()  {return value_;}

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

template<typename T>
struct test_numeric_udt {
  using value_type = T;
  test_numeric_udt(T i) : value_(i) {}
  test_numeric_udt (test_numeric_udt const& value) : value_ {value.value_}
  {}

  test_numeric_udt operator+ (test_numeric_udt const& x) { return test_numeric_udt{value_ + x.value_};}
  test_numeric_udt operator- (test_numeric_udt const& x) { return test_numeric_udt{value_ - x.value_};}
  test_numeric_udt operator* (test_numeric_udt const& x) { return test_numeric_udt{value_ * x.value_};}
  test_numeric_udt operator/ (test_numeric_udt const& x) { return test_numeric_udt{value_ / x.value_};}
  T const& value() const { return value_; }
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

#endif //ALGOL_EXAMPLES_UTILITY_HPP
