#ifndef ALGOL_PERF_STOPWATCH_HPP
#define ALGOL_PERF_STOPWATCH_HPP

#include <chrono>
#include "algol/io/manip.hpp"
#include "algol/perf/duration.hpp"

namespace algol::perf {
  /**
   * @class stopwatch
   * @brief keep track of elapsed time
   * @tparam DurationT unit of time
   * @tparam ClockT clock type
   */
  template <typename DurationT = std::chrono::nanoseconds, typename ClockT = std::chrono::steady_clock>
  class stopwatch {
  public:
    stopwatch () : start_time_(ClockT::now())
    {}

    void restart ()
    {
      start_time_ = ClockT::now();
    }

    DurationT elapsed () const
    {
      return std::chrono::duration_cast<DurationT>(ClockT::now() - start_time_);
    }

  private:
    friend std::ostream& operator<< (std::ostream& os, stopwatch const& value)
    {
      DurationT elapsed = value.elapsed();
      if (algol::io::is_in_compact_format(os)) {
        return os << elapsed.count() << ' ' << duration_string<DurationT>::symbol();
      }
      else {
        return os << "tick: " << ClockT::period::num << '/' << ClockT::period::den << ' '
                  << "steady: " << std::boolalpha << ClockT::is_steady << '\n'
                  << "elapsed: " << elapsed.count() << ' ' << duration_string<DurationT>::symbol() << std::endl;
      }
    }

    typename ClockT::time_point start_time_;
  };
}

#endif // ALGOL_PERF_STOPWATCH_HPP
