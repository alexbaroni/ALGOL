#ifndef ALGOL_ALGORITHMS_RECURSION_FACTORIAL_HPP
#define ALGOL_ALGORITHMS_RECURSION_FACTORIAL_HPP

#include <string>
#include <stdexcept>
#include "algol/math/math.hpp"
#include "stl2/concepts.hpp"

namespace algol::algorithms::recursion {
/**
 * \brief compute the factorial of n (n!)
 * \details the factorial is defined as follows
 * 0! = 1
 * n! = n * (n-1)!
 * \note referncial transparent function
 * \warning may overflow (eg fact(22) overflows an unsigned 64 bit integer)
 * \complexity O(N)
 * recurrence relation : T(0) = 1, T(N) = T(n-1) + 2 => 2n + 1 (+2 is for * and - operations)
 * maximun depth of recursion = N + 1 O(N)
 * \precondition n >= 0
 * \postcondition compute n!
 * \throws std::domain_error if n is a negative number (only signed types)
 * \tparam T the type of param and result
 * \param n the value to compute the factorial
 * \return n! (factorial of n)
 */
  namespace concepts = std::experimental::ranges;

  template <typename T>
  requires algol::math::Numeric<T>
  ||
  (
  concepts::CopyConstructible<T>&& concepts::StrictTotallyOrdered<T>
  &&
  !
  concepts::Same<concepts::value_type_t<T>, bool>&&
  algol::math::Differentiable<T> ()&&
  algol::math::Multipliable<T> ()
  )
  constexpr auto factorial(T
  n) -> T {
  using namespace std::literals::string_literals;

  if (n < 0)
  throw std::domain_error {
  "factorial is defined only for positive numbers"s
};
if (n == 0) return 1;
return
n* factorial(n - 1);
}
}

#endif //ALGOL_ALGORITHMS_RECURSION_FACTORIAL_HPP
