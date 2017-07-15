#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include "algol/io/pprint.hpp"
#include "algol/perf/stopwatch.hpp"
#include "algol/perf/operation_counter.hpp"

#define COMMA ,
PPRINT_DEFAULT_DECORATION(std::array<T COMMA N>, "[", "; ", "]", class T, std::size_t N)

template <typename T>
T kth_largest (std::vector<T> xs, std::size_t k)
{
  std::sort(std::begin(xs), std::end(xs), std::greater<T>());
  return xs[k - 1];
}

template <typename T>
T kth_largest2 (std::vector<T> xs, std::size_t k)
{
  std::sort(std::begin(xs), std::begin(xs) + k, std::greater<T>());

  for (auto x = std::begin(xs) + k; x != std::end(xs); ++x) {
    if (*x > xs[k - 1]) {
      xs[k - 1] = *x;
      std::sort(std::begin(xs), std::begin(xs) + k, std::greater<T>());
    }
  }

  return xs[k - 1];
}

int main ()
{
  using stopwatch = algol::perf::stopwatch<std::chrono::microseconds>;
  using operation_counter = algol::perf::operation_counter<std::int32_t, std::uint64_t>;

  std::vector<operation_counter> xs {5, 6, 9, 10, 23, 3, 8, 0, 22, 21};

  std::cout << "kth-largest" << std::endl;
  stopwatch sw;

  auto k = kth_largest(xs, 3);

  std::cout << sw << std::endl;
  std::cout << "3rd largest: " << k << std::endl;

  operation_counter::report(std::cout);

  std::cout << "kth-largest 2" << std::endl;
  operation_counter::reset();
  sw.restart();

  k = kth_largest2(xs, 3);

  std::cout << sw << std::endl;
  std::cout << "3rd largest: " << k << std::endl;
  operation_counter::report(std::cout);

  return 0;
}