#ifndef ALGOL_PERF_DURATION_HPP
#define ALGOL_PERF_DURATION_HPP

#include <chrono>

namespace algol::perf {
  template <typename DurationT>
  struct duration_string {
    static std::string symbol ()
    { return ""; }
  };

  template <>
  struct duration_string<std::chrono::nanoseconds> {
    static std::string symbol ()
    { return "ns"; }
  };

  template <>
  struct duration_string<std::chrono::microseconds> {
    static std::string symbol ()
    { return "us"; }
  };

  template <>
  struct duration_string<std::chrono::milliseconds> {
    static std::string symbol ()
    { return "ms"; }
  };

  template <>
  struct duration_string<std::chrono::seconds> {
    static std::string symbol ()
    { return "s"; }
  };
}

#endif //ALGOL_PERF_DURATION_HPP
