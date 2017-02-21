#include <iostream>
#include "algol/perf/stopwatch.hpp"
#include "algol/perf/operation_counter.hpp"
#include "algol/sequence/sequence.hpp"
#include "algol/sequence/generator/fibonacci_generator.hpp"

using operation_counter = algol::perf::operation_counter<std::uint32_t, std::uint64_t>;
using fibonacci_upto_n_seq = algol::sequence::fibonacci_upto_n_seq<operation_counter, 4000000>;

int main()
{
    using stopwatch = algol::perf::stopwatch<std::chrono::microseconds>;

    stopwatch sw;
    operation_counter sum = 0;
    fibonacci_upto_n_seq fibo_upto_n_seq;

    for(auto fn : fibo_upto_n_seq)
    {

        if ((fn & 1) == 0)
            sum += fn;
    }

    std::cout << sum << std::endl;
    std::cout << sw << std::endl;

    operation_counter::report(std::cout);
    return 0;
}