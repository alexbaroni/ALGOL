/**
 * \file
 * String to arithmetic convertion function.
 */

#ifndef ALGOL_RESULT_TO_HPP
#define ALGOL_RESULT_TO_HPP

#include <string>
#include <type_traits>
#include "algol/math/math.hpp"
#include "algol/result/result.hpp"

namespace algol {
  template<typename T, typename = std::enable_if_t<algol::math::is_numeric_v<T>>>
  auto to(std::string const& from) noexcept {
    try {
      if constexpr (std::is_same_v<T, float>)
        return make_result(std::stof(from));
      else if constexpr (std::is_same_v<T, double>)
        return make_result(std::stod(from));
      else if constexpr (std::is_same_v<T, long double>)
        return make_result(std::stold(from));
      else if constexpr (std::numeric_limits<T>::digits <= std::numeric_limits<unsigned long long>::digits) {
        if constexpr (std::numeric_limits<T>::is_signed) {
          if constexpr (std::numeric_limits<T>::digits < std::numeric_limits<intmax_t>::digits) {
            auto x = stoll(from);
            if (x > std::numeric_limits<T>::max() || x < std::numeric_limits<T>::min())
              return make_result<T>(std::make_error_code(std::errc::result_out_of_range));
            return make_result<T>(x);
          }
          else {
            auto x = stold(from);
            if (x > std::numeric_limits<T>::max() || x < std::numeric_limits<T>::min())
              return make_result<T>(std::make_error_code(std::errc::result_out_of_range));
            return make_result<T>(x);
          }
        }
        else {
          if constexpr (std::numeric_limits<T>::digits < std::numeric_limits<uintmax_t>::digits) {
            auto x = stoull(from);
            if (x > std::numeric_limits<T>::max())
              return make_result<T>(std::make_error_code(std::errc::result_out_of_range));
            return make_result<T>(x);
          }
          else {
            auto x = stold(from);
            if (x > std::numeric_limits<T>::max() || x < std::numeric_limits<T>::min())
              return make_result<T>(std::make_error_code(std::errc::result_out_of_range));
            return make_result<T>(x);
          }
        }
      }
      else {
        return make_result<T>(std::make_error_code(std::errc::not_supported));
      }
    }
    catch(std::out_of_range&) {
      return make_result<T>(std::make_error_code(std::errc::result_out_of_range));
    }
    catch(std::invalid_argument&) {
      return make_result<T>(std::make_error_code(std::errc::invalid_argument));
    }
    catch(...) {
      return make_result<T>(std::current_exception());
    }
  }
}

#endif //ALGOL_RESULT_TO_HPP
