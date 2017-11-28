#include <iostream>
#include <array>
#include <random>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <forward_list>
#include "pcg_random.hpp"
#include "algol/ds/array/array.hpp"
#include "algol/perf/stopwatch.hpp"
#include "algol/perf/benchmark.hpp"
#include "algol/algorithms/algorithm.hpp"
#include "algol/perf/operation_counter.hpp"
#include "algol/algorithms/sort/bubble_sort.hpp"
#include "algol/algorithms/sort/selection_sort.hpp"
#include "algol/algorithms/sort/insertion_sort.hpp"
#include "algol/algorithms/sort/shell_sort.hpp"

using stopwatch = algol::perf::stopwatch<std::chrono::nanoseconds>;
using operation_counter = algol::perf::operation_counter<int, std::uint64_t>;
using benchmark = algol::perf::benchmark<std::chrono::nanoseconds>;

using namespace algol::algorithms::sort;

const std::size_t BENCHMARK_RUNS = 100;
const std::size_t BENCHMARK_SIZE = 10000;
constexpr auto to_op_counter = [] (auto i) { return algol::perf::operation_counter<int>(i); };

std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> bench;

template <typename T, std::size_t N, typename URBG>
void build_random_array (std::array<T, N>& arr, URBG&& gen)
{
  std::uniform_int_distribution<int> distribution(0, N);
  for (auto& v : arr)
    v = distribution(gen);
}

template <typename ForwardIt, typename URBG>
void build_random_range (ForwardIt first, ForwardIt last, URBG&& gen)
{
  auto n = std::distance(first, last);
  std::uniform_int_distribution<int> distribution(-n, n);
  while (first != last) {
    *first = distribution(gen);
    ++first;
  }
}

template <typename URBG>
void init_bench_array (URBG&& gen)
{
  for (auto& v : bench)
    build_random_range(std::begin(v), std::end(v), gen);
}

int main ()
{
  // Seed with a real random value, if available
  pcg_extras::seed_seq_from<std::random_device> seed_source;

  // Make a random number engine
  pcg32 rng(seed_source);

  init_bench_array(rng);

  std::array<operation_counter, BENCHMARK_SIZE> array;
  build_random_array(array, rng);

  {
    std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> array = bench;
    auto run_num = 0;
    operation_counter::reset();
    auto result = benchmark::run_n("Average Bubble sort 100 times", BENCHMARK_RUNS, [&run_num, &array] () {
      bubble_sort_fast(std::begin(array[run_num]), std::end(array[run_num]));
      ++run_num;
    });
    std::cout << algol::io::compact << benchmark::run_average(result);
    std::cout << operation_counter::less_comparisons() / BENCHMARK_RUNS
              << ';' << operation_counter::swaps() / BENCHMARK_RUNS << ';' << std::endl;
  }

  {
    std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> array = bench;
    auto run_num = 0;
    operation_counter::reset();
    auto result = benchmark::run_n("Average Comb sort 100 times", BENCHMARK_RUNS, [&run_num, &array] () {
      comb_sort(std::begin(array[run_num]), std::end(array[run_num]));
      ++run_num;
    });
    std::cout << algol::io::compact << benchmark::run_average(result);
    std::cout << operation_counter::less_comparisons() / BENCHMARK_RUNS
              << ';' << operation_counter::swaps() / BENCHMARK_RUNS << ';' << std::endl;
  }

  {
    std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> array = bench;
    auto run_num = 0;
    operation_counter::reset();
    auto result = benchmark::run_n("Average Selection sort 100 times", BENCHMARK_RUNS, [&run_num, &array] () {
      selection_sort(std::begin(array[run_num]), std::end(array[run_num]));
      ++run_num;
    });
    std::cout << algol::io::compact << benchmark::run_average(result);
    std::cout << operation_counter::less_comparisons() / BENCHMARK_RUNS
              << ';' << operation_counter::swaps() / BENCHMARK_RUNS << ';' << std::endl;
  }

  {
    std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> array = bench;
    auto run_num = 0;
    operation_counter::reset();
    auto result = benchmark::run_n("Average STL Selection sort 100 times", BENCHMARK_RUNS, [&run_num, &array] () {
      selection_sort_stl(std::begin(array[run_num]), std::end(array[run_num]));
      ++run_num;
    });
    std::cout << algol::io::compact << benchmark::run_average(result);
    std::cout << operation_counter::less_comparisons() / BENCHMARK_RUNS
              << ';' << operation_counter::swaps() / BENCHMARK_RUNS << ';' << std::endl;
  }

  {
    std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> array = bench;
    auto run_num = 0;
    operation_counter::reset();
    auto result = benchmark::run_n("Average std Insertion sort 100 times", BENCHMARK_RUNS, [&run_num, &array] () {
      insertion_sort(std::begin(array[run_num]), std::end(array[run_num]));
      ++run_num;
    });
    std::cout << algol::io::compact << benchmark::run_average(result);
    std::cout << operation_counter::less_comparisons() / BENCHMARK_RUNS
              << ';' << operation_counter::swaps() / BENCHMARK_RUNS << ';' << std::endl;
  }

  {
    std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> array = bench;
    auto run_num = 0;
    operation_counter::reset();
    auto result = benchmark::run_n("Average STL Insertion sort 100 times", BENCHMARK_RUNS, [&run_num, &array] () {
      insertion_sort_stl(std::begin(array[run_num]), std::end(array[run_num]));
      ++run_num;
    });
    std::cout << algol::io::compact << benchmark::run_average(result);
    std::cout << operation_counter::less_comparisons() / BENCHMARK_RUNS
              << ';' << operation_counter::swaps() / BENCHMARK_RUNS << ';' << std::endl;
  }

  {
    std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> array = bench;
    auto run_num = 0;
    operation_counter::reset();
    auto result = benchmark::run_n("Average Insertion sort 100 times", BENCHMARK_RUNS, [&run_num, &array] () {
      insertion_sort(std::begin(array[run_num]), std::end(array[run_num]));
      ++run_num;
    });
    std::cout << algol::io::compact << benchmark::run_average(result);
    std::cout << operation_counter::less_comparisons() / BENCHMARK_RUNS
              << ';' << operation_counter::swaps() / BENCHMARK_RUNS << ';' << std::endl;
  }

  {
    std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> array = bench;
    auto run_num = 0;
    operation_counter::reset();
    auto result = benchmark::run_n("Average Shell sort 100 times", BENCHMARK_RUNS, [&run_num, &array] () {
      shell_sort(std::begin(array[run_num]), std::end(array[run_num]));
      ++run_num;
    });
    std::cout << algol::io::compact << benchmark::run_average(result);
    std::cout << operation_counter::less_comparisons() / BENCHMARK_RUNS
              << ';' << operation_counter::swaps() / BENCHMARK_RUNS << ';' << std::endl;
  }

  {
    std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> array = bench;
    auto run_num = 0;
    operation_counter::reset();
    auto result = benchmark::run_n("Average Shell sort (ciura gaps) 100 times", BENCHMARK_RUNS, [&run_num, &array] () {
      shell_sort_ciura_gaps(std::begin(array[run_num]), std::end(array[run_num]));
      ++run_num;
    });
    std::cout << algol::io::compact << benchmark::run_average(result);
    std::cout << operation_counter::less_comparisons() / BENCHMARK_RUNS
              << ';' << operation_counter::swaps() / BENCHMARK_RUNS << ';' << std::endl;
  }

  return 0;
}
