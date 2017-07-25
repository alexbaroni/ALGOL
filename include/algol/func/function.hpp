#ifndef ALGOL_FUNC_FUNCTION_HPP
#define ALGOL_FUNC_FUNCTION_HPP

#include <utility>

namespace algol {
  static constexpr struct identity_ {
    template<typename T>
    constexpr auto operator() (T&& x) const noexcept
    {
      return x;
    }
  } identity{};
}

#endif //ALGOL_FUNC_FUNCTION_HPP
