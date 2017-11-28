#include <iostream>
#include <array>
#include <cassert>
#include <algorithm>
#include <random>
#include <iterator>
#include <forward_list>
#include "pcg_random.hpp"
#include "../utility/utility.hpp"
#include "algol/func/function.hpp"
#include "algol/ds/array/array.hpp"
#include "algol/perf/stopwatch.hpp"
#include "algol/algorithms/algorithm.hpp"
#include "algol/perf/benchmark.hpp"
#include "algol/perf/operation_counter.hpp"
#include "algol/algorithms/sort/insertion_sort.hpp"

using stopwatch = algol::perf::stopwatch<std::chrono::nanoseconds>;
using operation_counter = algol::perf::operation_counter<int, std::uint64_t>;
using benchmark = algol::perf::benchmark<std::chrono::nanoseconds>;

const std::size_t BENCHMARK_RUNS = 100;
const std::size_t BENCHMARK_SIZE = 1000;

constexpr auto to_op_counter = [] (auto i) { return algol::perf::operation_counter<int>(i); };

std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> bench;

template <typename T, std::size_t N>
constexpr auto build_reverse_array ()
{
  std::array<T, N> arr = algol::ds::fill_array<N>(to_op_counter);
  algol::algorithms::reverse(std::begin(arr), std::end(arr));
  return arr;
}

template <typename T, std::size_t N, typename URBG>
void build_random_array (std::array<T, N>& arr, URBG&& gen)
{
  std::uniform_int_distribution<int> distribution(0, N);
  for (auto& v : arr)
    v = distribution(gen);
}

template <typename URBG>
void init_bench_array (URBG&& gen)
{
  for (auto& v : bench)
    build_unsorted_range(std::begin(v), std::end(v), -BENCHMARK_SIZE, BENCHMARK_SIZE, gen);
}

int main ()
{
  using namespace algol::algorithms::sort;

  // Seed with a real random value, if available
  pcg_extras::seed_seq_from<std::random_device> seed_source;

  // Make a random number engine
  pcg32 rng(seed_source);

  init_bench_array(rng);

  std::cout << "Insertion sort reverse order using STL algorithms" << std::endl;
  {
    std::cout << std::endl << "10 elements:" << std::endl;
    std::array<operation_counter, 10> arr = build_reverse_array<operation_counter, 10>();
    operation_counter::reset();
    stopwatch sw;
    insertion_sort_stl(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "100 elements:" << std::endl;
    std::array<operation_counter, 100> arr = build_reverse_array<operation_counter, 100>();
    operation_counter::reset();
    stopwatch sw;
    insertion_sort_stl(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "1000 elements:" << std::endl;
    std::array<operation_counter, 1000> arr = build_reverse_array<operation_counter, 1000>();
    operation_counter::reset();
    stopwatch sw;
    insertion_sort_stl(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "Insertion sort (forward_list)" << std::endl;
    std::forward_list<operation_counter> lst;
    for (auto i = 0; i < 10; ++i)
      lst.push_front(algol::perf::operation_counter<int>(i));
    operation_counter::reset();
    stopwatch sw;
    insertion_sort_stl(std::begin(lst), std::end(lst));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(lst), std::end(lst)));
  }

  {
    std::cout << std::endl << "Insertion sort random order" << std::endl;
    std::array<operation_counter, 1000> arr;
    build_random_array(arr, rng);
    operation_counter::reset();
    stopwatch sw;
    insertion_sort_stl(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  std::cout << "Insertion sort reverse order" << std::endl;
  {
    std::cout << std::endl << "10 elements:" << std::endl;
    std::array<operation_counter, 10> arr = build_reverse_array<operation_counter, 10>();
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "100 elements:" << std::endl;
    std::array<operation_counter, 100> arr = build_reverse_array<operation_counter, 100>();
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "1000 elements:" << std::endl;
    std::array<operation_counter, 1000> arr = build_reverse_array<operation_counter, 1000>();
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "Insertion sort (forward_list)" << std::endl;
    std::forward_list<operation_counter> lst;
    for (auto i = 0; i < 10; ++i)
      lst.push_front(algol::perf::operation_counter<int>(i));
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(lst), std::end(lst));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(lst), std::end(lst)));
  }

  {
    std::cout << std::endl << "Insertion sort random order" << std::endl;
    std::array<operation_counter, 1000> arr;
    build_random_array(arr, rng);
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  std::cout << "Bidir Insertion sort reverse order" << std::endl;
  {
    std::cout << std::endl << "10 elements:" << std::endl;
    std::array<operation_counter, 10> arr = build_reverse_array<operation_counter, 10>();
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "100 elements:" << std::endl;
    std::array<operation_counter, 100> arr = build_reverse_array<operation_counter, 100>();
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "1000 elements:" << std::endl;
    std::array<operation_counter, 1000> arr = build_reverse_array<operation_counter, 1000>();
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "Insertion sort random order" << std::endl;
    std::array<operation_counter, 1000> arr;
    build_random_array(arr, rng);
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  std::cout << std::endl << "Std 1000 elements:" << std::endl;
  {
    std::cout << std::endl << "sorted elements:" << std::endl;
    std::array<operation_counter, BENCHMARK_SIZE> arr;
    build_sorted_range(std::begin(arr), std::end(arr), -5);
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }
  {
    std::cout << std::endl << "mostly sorted elements:" << std::endl;
    std::array<operation_counter, BENCHMARK_SIZE> arr;
    build_mostly_sorted_range(std::begin(arr), std::end(arr), -5);
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }
  {
    std::cout << std::endl << "reverse sorted elements:" << std::endl;
    std::array<operation_counter, BENCHMARK_SIZE> arr;
    build_reverse_sorted_range(std::begin(arr), std::end(arr), -5);
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }
  {
    std::cout << std::endl << "mostly reverse sorted elements:" << std::endl;
    std::array<operation_counter, BENCHMARK_SIZE> arr;
    build_mostly_reverse_sorted_range(std::begin(arr), std::end(arr), -5);
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }
  {
    std::cout << std::endl << "unsorted elements:" << std::endl;
    std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> array = bench;
    auto run_num = 0;
    operation_counter::reset();
    auto result = benchmark::run_n(BENCHMARK_RUNS, [&run_num, &array] () {
      insertion_sort(std::begin(array[run_num]), std::end(array[run_num]));
      ++run_num;
    });
    std::cout << benchmark::run_average(result);
    std::cout << "< " << operation_counter::less_comparisons() / BENCHMARK_RUNS
              << " swaps " << operation_counter::swaps() / BENCHMARK_RUNS << std::endl;
    //assert(std::is_sorted(std::begin(array), std::end(array)));
  }

  std::cout << std::endl << "Bidir 1000 elements:" << std::endl;
  {
    std::cout << std::endl << "sorted elements:" << std::endl;
    std::array<operation_counter, BENCHMARK_SIZE> arr;
    build_sorted_range(std::begin(arr), std::end(arr), -5);
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }
  {
    std::cout << std::endl << "mostly sorted elements:" << std::endl;
    std::array<operation_counter, BENCHMARK_SIZE> arr;
    build_mostly_sorted_range(std::begin(arr), std::end(arr), -5);
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }
  {
    std::cout << std::endl << "reverse sorted elements:" << std::endl;
    std::array<operation_counter, BENCHMARK_SIZE> arr;
    build_reverse_sorted_range(std::begin(arr), std::end(arr), -5);
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }
  {
    std::cout << std::endl << "mostly reverse sorted elements:" << std::endl;
    std::array<operation_counter, BENCHMARK_SIZE> arr;
    build_mostly_reverse_sorted_range(std::begin(arr), std::end(arr), -5);
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }
  {
    std::cout << std::endl << "unsorted elements:" << std::endl;
    std::array<std::array<operation_counter, BENCHMARK_SIZE>, BENCHMARK_RUNS> array = bench;
    auto run_num = 0;
    operation_counter::reset();
    auto result = benchmark::run_n(BENCHMARK_RUNS, [&run_num, &array] () {
      insertion_sort(std::begin(array[run_num]), std::end(array[run_num]));
      ++run_num;
    });
    std::cout << benchmark::run_average(result);
    std::cout << "< " << operation_counter::less_comparisons() / BENCHMARK_RUNS
              << " swaps " << operation_counter::swaps() / BENCHMARK_RUNS << std::endl;
    //assert(std::is_sorted(std::begin(array), std::end(array)));
  }
  return 0;
}
