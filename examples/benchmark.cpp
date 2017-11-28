#include <iostream>
#include <cassert>
#include "algol/perf/benchmark.hpp"
#include "algol/perf/operation_counter.hpp"

using operation_counter = algol::perf::operation_counter<std::int64_t, std::uint64_t>;

long fibonacci (unsigned n)
{
  if (n < 2) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

operation_counter fibo (operation_counter n)
{
  if (n < 2) return n;
  return fibo(n - 1) + fibo(n - 2);
}

int main ()
{
  using benchmark = algol::perf::benchmark<std::chrono::microseconds>;

  std::cout << benchmark::clock_type::period::num << '/' << benchmark::clock_type::period::den << std::endl;

  auto res = benchmark::run("fibo 28", fibonacci, 28);
  std::cout << res << std::endl;

  auto result = benchmark::run_n("fibo 28 (1000) times", 1000, fibonacci, 28);
  assert(result.size() == 1000);
  std::cout << benchmark::run_average(result) << std::endl;

  res = benchmark::run("fibo 28", fibonacci, 28);
  std::cout << algol::io::compact << res << std::endl;

  result = benchmark::run_n("fibo 28 (1000) times", 1000, fibonacci, 28);
  assert(result.size() == 1000);
  std::cout << algol::io::compact << benchmark::run_average(result) << std::endl;

  res = benchmark::run("fibo 28", fibonacci, 28);
  std::cout << std::endl << algol::io::nocompact << res << std::endl;

  auto res1 = benchmark::run("fibo 28 operation_counter", fibo, 28);
  std::cout << algol::io::compact << res1
            << operation_counter::report << std::endl;
  return 0;
}