// A compilation of the following posts:
// http://stackoverflow.com/questions/18648069/g-doesnt-compile-constexpr-function-with-assert-in-it
// http://ericniebler.com/2014/09/27/assert-and-constexpr-in-cxx11/
// taken here: https://gist.github.com/oliora/928424f7675d58fadf49c70fdba70d2f

#ifndef ALGOL_UTILITY_HPP
#define ALGOL_UTILITY_HPP

#include <cassert>
#include <utility>

namespace algol {
  template <class Assert>
  inline void constexpr_assert_failed (Assert&& a) noexcept
  { std::forward<Assert>(a)(); }

}
// When evaluated at compile time emits a compilation error if condition is not true.
// Invokes the standard assert at run time.
#define constexpr_assert(cond) \
    ((void)((cond) ? 0 : (algol::constexpr_assert_failed([](){ assert(!#cond);}), 0)))

#endif //ALGOL_UTILITY_HPP
