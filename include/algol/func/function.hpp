#ifndef ALGOL_FUNC_FUNCTION_HPP
#define ALGOL_FUNC_FUNCTION_HPP

#include <utility>

namespace algol {
  static constexpr struct identity_ {
    template <typename T>
    constexpr auto operator() (T&& x) const noexcept
    {
      return x;
    }
  } identity {};

  template <typename C>
  constexpr auto full (C const& c) -> decltype(c.full())
  {
    return c.full();
  }

  template <typename C>
  constexpr auto top (C& c) -> decltype(c.top())
  {
    return c.top();
  }

  template <typename C>
  constexpr auto top (C const& c) -> decltype(c.top())
  {
    return c.top();
  }

  template <typename C, typename... Args>
  constexpr auto push (C& c, Args&& ... args) -> decltype(c.push(std::forward<Args>(args)...))
  {
    c.push(std::forward<Args>(args)...);
  }

  template <typename C>
  constexpr auto pop (C const& c) -> decltype(c.pop())
  {
    return c.pop();
  }

  template <typename C>
  constexpr auto clear (C const& c) -> decltype(c.clear())
  {
    return c.clear();
  }
}

#endif //ALGOL_FUNC_FUNCTION_HPP
