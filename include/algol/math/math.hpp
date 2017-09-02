/**
 * \file
 * Math functions.
 */

#ifndef ALGOL_MATH_MATH_HPP
#define ALGOL_MATH_MATH_HPP

#include <cmath>
#include <type_traits>
/*
EDOM	          FE_INVALID          std::domain_error
ERANGE	        FE_DIVBYZERO        std::domain_error
ERANGE	        FE_OVERFLOW         std::overflow_error
ERANGE          FE_UNDERFLOW        std::underflow_error
or unchanged    or nothing
unchanged	      FE_INEXACT          std::range_error
or nothing
(unspecified)
*/

namespace algol::math {
  template<typename T>
  struct is_numeric : std::integral_constant<bool, std::is_arithmetic_v<T> && !std::is_same_v<T, bool>> {};

  template<typename T>
  inline constexpr bool is_numeric_v = is_numeric<T>::value;

  template<typename T>
  concept bool Numeric = algol::math::is_numeric_v<T>;

  template <class T>
  concept bool Addable() {
    return requires(T a, T b) { {a + b} -> T; };
  }

  template <class T>
  concept bool Differentiable() {
    return requires(T a, T b) { {a - b} -> T; };
  }

  template <class T>
  concept bool Multipliable() {
    return requires(T a, T b) { {a * b} -> T; };
  }

  template <class T>
  concept bool Dividable() {
    return requires(T a, T b) { {a / b} -> T; };
  }

  /**
   * Generic modulo function works with every arithmetic type
   * @tparam T the type of operands
   * @param dividend
   * @param divisor
   * @return dividend mod divisor
   */
  template<typename T, typename = std::enable_if_t<is_numeric_v<T>>>
  constexpr auto mod (T dividend, T divisor) {
    if constexpr (std::is_floating_point_v<T>)
      return std::fmod(dividend, divisor);
    else
      return dividend % divisor;
  }

  /**
   * Floating point equality comparison
   * @tparam T T the type of operands
   * @param a lhs term
   * @param b rhs term
   * @return true if they are nearly equal
   */
  template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
  auto nearly_equal (T a, T b)
  {
    return b > std::nextafter(a, std::numeric_limits<T>::lowest())
           && b < std::nextafter(a, std::numeric_limits<T>::max());
  }

  /**
   * Floating point equality comparison
   * @tparam T T the type of operands
   * @param a lhs term
   * @param b rhs term
   * @param factor a factor of epsilon
   * @return true if they are nearly equal
   */

  template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
  auto nearly_equal (T a, T b, int factor)
  {
    auto min_a = a - (a - std::nextafter(a, std::numeric_limits<T>::lowest())) * factor;
    auto max_a = a + (std::nextafter(a, std::numeric_limits<T>::max()) - a) * factor;
    return b > min_a && b < max_a;
  }
}

#endif //ALGOL_MATH_MATH_HPP
