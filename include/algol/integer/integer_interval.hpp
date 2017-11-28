#ifndef ALGOL_INTEGER_INTEGER_INTERVAL_HPP
#define ALGOL_INTEGER_INTEGER_INTERVAL_HPP

#include <type_traits>
#include <iosfwd>
#include <iomanip>
#include <limits>
#include <boost/io/ios_state.hpp>

namespace algol::integer {
  template <typename T,
      typename = std::enable_if_t<(std::is_integral_v<T> || std::is_convertible_v<T, int>) && !std::is_same_v<T, bool>>>
  class integer_interval {
  public:
    typedef T base_type;

    integer_interval () : integer_interval(T{}, T{})
    {}

    integer_interval (T lower, T upper) : lower_(lower), upper_(upper)
    {}

    integer_interval (integer_interval const&) = default;
    integer_interval& operator= (integer_interval const&) = default;
    ~integer_interval () = default;

    T const& lower () const
    { return lower_; }

    T const& upper () const
    { return upper_; }

    bool is_empty () const
    { return lower_ >= upper_; }

    void set_empty ()
    {
      lower_ = T{};
      upper_ = T{};
    }

  private:
    T lower_;
    T upper_;
  };

  template <class T>
  inline
  bool empty (integer_interval<T> const& x)
  {
    return x.is_empty();
  }

  template <class T>
  inline
  const T& lower (integer_interval<T> const& x)
  {
    return x.lower();
  }

  template <class T>
  inline
  const T& upper (integer_interval<T> const& x)
  {
    return x.upper();
  }

  template <class T>
  inline
  T width (integer_interval<T> const& x)
  {
    if (x.is_empty())
      return T{};
    else
      return x.upper() - x.lower() + static_cast<T>(1);
  }

  template <class T>
  inline
  bool in (T const& x, integer_interval<T> const& y)
  {
    if (y.is_empty())
      return false;
    else
      return x >= y.lower() && x <= y.upper();
  }

  template <class CharType, class CharTraits, class T>
  std::basic_istream<CharType, CharTraits>& operator>>
      (std::basic_istream<CharType, CharTraits>& stream, integer_interval<T>& value)
  {
    T lower, upper;

    if (stream.peek() == ' ')
      stream.ignore(std::numeric_limits<std::streamsize>::max(), ' ');

    if (stream.peek() == '[' || stream.peek() == '(')
      stream.ignore();

    stream >> lower;

    if (stream.peek() == ',' || stream.peek() == ';')
      stream.ignore();

    stream >> upper;

    if (stream.peek() == ']' || stream.peek() == ')')
      stream.ignore();

    if (stream)
      value = integer_interval<T>(lower, upper);

    return stream;
  }

  template <class CharType, class CharTraits, class T>
  std::basic_ostream<CharType, CharTraits>& operator<<
      (std::basic_ostream<CharType, CharTraits>& stream, integer_interval<T> const& value)
  {
    boost::io::ios_all_saver ias(stream);

    stream << std::setw(0) << std::dec << std::noshowbase;
    if (empty(value))
      return stream << "[]";
    else
      return stream << '[' << lower(value) << ',' << upper(value) << ']';
  }
}

#endif // ALGOL_INTEGER_INTEGER_INTERVAL_HPP