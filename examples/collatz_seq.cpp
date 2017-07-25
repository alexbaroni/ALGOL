#include <iostream>
#include "algol/perf/stopwatch.hpp"
#include "algol/perf/operation_counter.hpp"
#include "algol/integer/integer_interval.hpp"
#include "algol/integer/integer_interval_range.hpp"

int main ()
{
  using stopwatch = algol::perf::stopwatch<std::chrono::microseconds>;
  using interval = algol::integer::integer_interval<uint32_t>;
  using interval_range = algol::integer::integer_interval_range<interval::base_type>;
  using operation_counter = algol::perf::operation_counter<std::uint32_t, std::uint64_t>;
  using interval_op_count = algol::integer::integer_interval<operation_counter>;
  using interval_range_op_count = algol::integer::integer_interval_range<operation_counter>;

  stopwatch sw;

  interval int_interval {11, 20};
  std::cout << "n " << " - " << "length" << std::endl;
  for (const auto& l : interval_range(int_interval)) {
    interval::base_type c = 1;
    interval::base_type n = l;

    do {
      if ((n & 1) == 0)
        n = n >> 1;
      else
        n = 3 * n + 1;

      c++;
    } while (n != 1);

    std::cout << l << " - " << c << std::endl;
  }

  std::cout << sw << std::endl;

  interval_op_count iop {11, 20};
  std::cout << "operation_counter" << std::endl;
  std::cout << "n " << " - " << "length" << std::endl;
  sw.restart();
  for (const auto& l : interval_range_op_count(iop)) {
    interval_op_count::base_type c = 1;
    interval_op_count::base_type n = l;

    do {
      if ((n & 1) == 0)
        n = n >> 1;
      else
        n = 3 * n + 1;

      c++;
    } while (n != 1);

    std::cout << l << " - " << c << std::endl;
  }

  std::cout << sw << std::endl;
  operation_counter::report(std::cout);
  return 0;
}