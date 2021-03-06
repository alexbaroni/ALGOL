#include <iostream>
#include "algol/perf/stopwatch.hpp"
#include "algol/perf/operation_counter.hpp"
#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/fibonacci_generator.hpp"

int main ()
{
  using stopwatch = algol::perf::stopwatch<std::chrono::microseconds>;
  using operation_counter = algol::perf::operation_counter<std::uint32_t, std::uint64_t>;
  using fibonacci_upto_n_seq = algol::sequence::fibonacci_upto_n_seq<operation_counter>;
  using even_fibonacci_upto_n_seq = algol::sequence::even_fibonacci_upto_n_seq<operation_counter>;

  std::cout << "sequence" << std::endl;

  stopwatch sw;
  operation_counter sum = 0;
  fibonacci_upto_n_seq fibo_upto_n_seq {4000000};
  even_fibonacci_upto_n_seq even_fibo_upto_n {4000000};

  for (auto fn : fibo_upto_n_seq) {
    if ((fn & 1) == 0)
      sum += fn;
  }

  std::cout << sw << std::endl;
  std::cout << sum << std::endl;

  std::cout << operation_counter::report;
  std::cout << std::endl;

  std::cout << "even sequence" << std::endl;
  operation_counter::reset();
  sum = 0;
  sw.restart();

  for (auto fn : even_fibo_upto_n) {
    sum += fn;
  }

  std::cout << algol::io::compact << sw << std::endl;
  std::cout << sum << std::endl;

  std::cout << operation_counter::report;
  return 0;
}