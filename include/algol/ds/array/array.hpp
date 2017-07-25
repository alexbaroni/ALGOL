#ifndef ALGOL_DS_ARRAY_HPP
#define ALGOL_DS_ARRAY_HPP

#include <array>

namespace algol::ds {

  template<std::size_t N, typename Function>
  constexpr auto fill_array (Function&& f) -> std::array<std::invoke_result_t<std::decay_t<Function>, std::size_t>, N>
  {
    std::array<std::invoke_result_t<std::decay_t<Function>, std::size_t>, N> array{};
    for (std::size_t i = 0; i < N; ++i)
      array[i] = f(i);
    return array;
  }
}

#endif //ALGOL_DS_ARRAY_HPP
