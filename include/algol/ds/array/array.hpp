/**
 * \file
 * Array utilities
 */

#ifndef ALGOL_DS_ARRAY_HPP
#define ALGOL_DS_ARRAY_HPP

#include <array>
#include <functional>

namespace algol::ds {
  /**
   * \brief Fill an array with the function provided
   * \precondition None
   * \postcondition Array filled with N items
   * \complexity O(N)
   * \tparam N array size
   * \tparam F generating function type
   * \tparam Args function F arguments type
   * \tparam R rseult type of invoking F with Args
   * \param f generating function
   * \param args function f arguments
   * \return array<R, N> filled using function f
   */
  template <std::size_t N, typename F, typename ...Args,
      typename R = std::invoke_result_t<std::decay_t<F>, std::size_t, std::decay_t<Args>...>>
  constexpr auto fill_array (F&& f, Args&& ... args) noexcept(std::is_nothrow_invocable_r_v<R, F, std::size_t, Args...>)
  {
    std::array<R, N> vs{};
    for (std::size_t i{0}; i < N; ++i)
      vs[i] = std::invoke(std::forward<decltype(f)>(f), i, std::forward<Args>(args)...);
    return vs;
  }
}

#endif //ALGOL_DS_ARRAY_HPP
