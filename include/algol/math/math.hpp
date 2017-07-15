/**
 * \file
 * Math functions.
 */

#ifndef ALGOL_MATH_MATH_HPP
#define ALGOL_MATH_MATH_HPP

#include <cmath>

namespace algol {
  namespace math {
    /**
     * Generic modulo function works with every arithmetic type
     * @tparam T the type of operands
     * @param dividend
     * @param divisor
     * @return dividend mod divisor
     */
    template <typename T>
    auto mod (T dividend, T divisor)
    {
      static_assert(std::is_arithmetic_v<T> && !std::is_same_v<T, bool>);
      if constexpr (std::is_floating_point_v<T>)
        return std::fmod(dividend, divisor);
      else
        return dividend % divisor;
    }
  }
}

#endif //ALGOL_MATH_MATH_HPP
