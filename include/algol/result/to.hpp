/**
 * \file
 * String to arithmetic convertion function.
 */

#ifndef ALGOL_RESULT_TO_HPP
#define ALGOL_RESULT_TO_HPP

#include <string>
#include <type_traits>
#include "algol/result/result.hpp"

namespace algol {
  template <typename T>
  auto to (std::string const& from) -> result<T>
  {
    static_assert(std::is_arithmetic_v<T> && !std::is_same_v<T, bool>);
    try {
      if constexpr (std::is_same_v<T, float>)
        return std::stof(from);
      else if constexpr (std::is_same_v<T, double>)
        return std::stod(from);
      else if constexpr (std::is_same_v<T, long double>)
        return std::stold(from);
      else if constexpr (std::is_same_v<T, long> || std::is_same_v<T, unsigned long>)
        return std::stol(from);
      else if constexpr (std::is_same_v<T, long long> || std::is_same_v<T, unsigned long long>)
        return std::stoll(from);
      else if constexpr (std::numeric_limits<T>::digits <= std::numeric_limits<unsigned int>::digits)
        return std::stoi(from);
      else
        return make_result(std::make_error_code(std::errc::not_supported));
    }
    catch (...) {
      return make_result<T>(std::current_exception());
    }
  }
}

#endif //ALGOL_RESULT_TO_HPP
