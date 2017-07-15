#include <iostream>
#include "algol/perf/stopwatch.hpp"
#include "algol/perf/operation_counter.hpp"
#include <algol/integer/integer_interval.hpp>
#include "algol/integer/integer_interval_range.hpp"
#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/collatz_generator.hpp"

using operation_counter = algol::perf::operation_counter<std::uint32_t, std::uint64_t>;
using interval_op_count = algol::integer::integer_interval<operation_counter>;
using interval_range_op_count = algol::integer::integer_interval_range<operation_counter>;
using collatz_seq = algol::sequence::collatz_seq<operation_counter>;

int main ()
{
  using stopwatch = algol::perf::stopwatch<std::chrono::microseconds>;

  stopwatch sw;

  interval_op_count iop {11, 20};
  std::cout << "n " << " - " << "length" << std::endl;
  for (auto l : interval_range_op_count(iop)) {
    collatz_seq seq {l};

    std::cout << l << " - " << std::distance(std::begin(seq), std::end(seq)) << std::endl;
  }

  std::cout << sw << std::endl;
  operation_counter::report(std::cout);
  return 0;
}