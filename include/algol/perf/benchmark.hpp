#ifndef ALGOL_PERF_BENCHMARK_HPP
#define ALGOL_PERF_BENCHMARK_HPP

#include <chrono>
#include <functional>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include "algol/io/manip.hpp"
#include "algol/perf/duration.hpp"
#include "algol/perf/stopwatch.hpp"

namespace algol::perf {
  template <typename D, typename R>
  struct benchmark_result {
    std::string name;
    D duration;
    R result;
  private:
    friend std::ostream& operator<< (std::ostream& os, benchmark_result const& value)
    {
      if (algol::io::is_in_compact_format(os)) {
        if (!std::empty(value.name))
          os << value.name << ';';
        return os << value.duration.count() << ';' << D::period::num << '/' << D::period::den << ';'
                  << value.result << ';';
      }
      else {
        if (!std::empty(value.name))
          os << value.name << std::endl;
        return os << "elapsed: " << value.duration.count() << ' ' << duration_string<D>::symbol() << std::endl
                  << "result: " << value.result << std::endl;
      }
    }
  };

  template <typename D>
  struct benchmark_result<D, void> {
    std::string name;
    D duration;
  private:
    friend std::ostream& operator<< (std::ostream& os, benchmark_result const& value)
    {
      if (algol::io::is_in_compact_format(os)) {
        if (!std::empty(value.name))
          os << value.name << ';';
        return os << value.duration.count() << ';' << D::period::num << '/' << D::period::den << ';';
      }
      else {
        if (!std::empty(value.name))
          os << value.name << std::endl;
        return os << "elapsed: " << value.duration.count() << ' ' << duration_string<D>::symbol() << std::endl;
      }
    }
  };

  template <typename DurationT = std::chrono::nanoseconds, typename ClockT = std::chrono::steady_clock>
  struct benchmark {
    using duration_type = DurationT;
    using clock_type = ClockT;

    template <typename F, typename ...Args, typename R = std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>>
    static auto run (F&& f, Args&& ... args)
    {
      using namespace std::literals::string_literals;
      return run(""s, std::forward<decltype(f)>(f), std::forward<Args>(args)...);
    }

    template <typename F, typename ...Args, typename R = std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>>
    static auto run (std::string const& name, F&& f, Args&& ... args)
    {
      auto result = benchmark_result<DurationT, R>{};
      result.name = name;

      auto sw = stopwatch<DurationT, ClockT>{};
      if constexpr (std::is_void_v<R>)
      {
        std::apply(std::forward<decltype(f)>(f), std::make_tuple(std::forward<Args>(args)...));
      }
      else {
        result.result = std::apply(std::forward<decltype(f)>(f), std::make_tuple(std::forward<Args>(args)...));
      }
      result.duration = sw.elapsed();
      return result;
    }

    template <typename F, typename ...Args, typename R = std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>>
    static auto run_n (std::size_t count, F&& f, Args&& ... args)
    {
      using namespace std::literals::string_literals;
      return run_n(""s, count, std::forward<decltype(f)>(f), std::forward<Args>(args)...);
    }

    template <typename F, typename ...Args, typename R = std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>>
    static auto run_n (std::string const& name, std::size_t count, F&& f, Args&& ... args)
    {
      std::vector<benchmark_result<DurationT, R>> result;
      result.reserve(count);
      for (std::size_t i = 0; i < count; ++i)
        result.emplace_back(benchmark::run(name, std::forward<decltype(f)>(f), std::forward<Args>(args)...));

      return result;
    }

    template <typename R>
    static auto run_average (std::vector<benchmark_result<DurationT, R>> const& vs)
    {
      benchmark_result<DurationT, void> result {};

      if (!std::empty(vs)) {
        result.duration = std::accumulate(std::next(std::begin(vs)), std::end(vs), vs[0].duration,
                                          [] (auto a, auto b) {
                                            return a + b.duration;
                                          });
        result.duration /= vs.size();
        result.name = vs[0].name;
      }
      return result;
    }
  };
}

#endif //ALGOL_PERF_BENCHMARK_HPP
