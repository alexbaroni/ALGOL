/**
 * \file
 * Math functions.
 */

#ifndef ALGOL_MATH_MATH_HPP
#define ALGOL_MATH_MATH_HPP

#include <cmath>

namespace algol {
  namespace math {
    template<typename T>
    auto mod(T dividend, T divisor) {
      if constexpr (std::is_floating_point_v<T>)
      return std::fmod(dividend, divisor);
      else
      return dividend % divisor;
    }
  }
}

#endif //ALGOL_MATH_MATH_HPP
