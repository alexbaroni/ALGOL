#ifndef ALGOL_PERF_STOPWATCH_HPP
#define ALGOL_PERF_STOPWATCH_HPP

#include <chrono>

namespace algol { namespace perf {
    template<typename DurationT>
    struct duration_string
    {
        static std::string symbol() { return ""; }
    };

    template<>
    struct duration_string<std::chrono::nanoseconds>
    {
        static std::string symbol() { return "ns"; }
    };

    template<>
    struct duration_string<std::chrono::microseconds>
    {
        static std::string symbol() { return "us"; }
    };

    template<>
    struct duration_string<std::chrono::milliseconds>
    {
        static std::string symbol() { return "ms"; }
    };

    template<>
    struct duration_string<std::chrono::seconds>
    {
        static std::string symbol() { return "s"; }
    };

    template<typename DurationT = std::chrono::nanoseconds, typename ClockT = std::chrono::steady_clock>
    class stopwatch
    {
    public:
        stopwatch() : start_time_(ClockT::now()) {}

        void restart() {
            start_time_ = ClockT::now();
        }

        DurationT elapsed() const {
            return std::chrono::duration_cast<DurationT>(ClockT::now() - start_time_);
        }

    private:
        friend std::ostream& operator<<(std::ostream& os, stopwatch const& value)
        {
            DurationT elapsed = value.elapsed();
            return os << "tick: " << ClockT::period::num << "/" << ClockT::period::den << " "
                      << "steady: " << std::boolalpha << ClockT::is_steady << '\n'
                      << "elapsed: " << elapsed.count() << " " << duration_string<DurationT>::symbol() << std::endl;
        }

        typename ClockT::time_point start_time_;
    };
}}

#endif // ALGOL_PERF_STOPWATCH_HPP
