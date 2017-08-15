#include <iostream>
#include <cassert>
#include "algol/perf/benchmark.hpp"

long fibonacci(unsigned n)
{
  if (n < 2) return n;
  return fibonacci(n-1) + fibonacci(n-2);
}

int main ()
{
  using benchmark = algol::perf::benchmark<std::chrono::microseconds>;

  std::cout << benchmark::clock_type::period::num << '/' << benchmark::clock_type::period::den << std::endl;

  auto res =  benchmark::run(fibonacci, 28);
  std::cout << res << std::endl;

  auto result = benchmark::run_n(1000, fibonacci, 28);
  assert(result.size() == 1000);
  std::cout << benchmark::run_average(result) << std::endl;
  return 0;
}