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
#include <algol/algorithms/algorithm.hpp>
#include "algol/perf/operation_counter.hpp"
#include "algol/algorithms/sort/bubble_sort.hpp"
#include "algol/algorithms/sort/selection_sort.hpp"
#include "algol/algorithms/sort/insertion_sort.hpp"

using stopwatch = algol::perf::stopwatch<std::chrono::nanoseconds>;
using operation_counter = algol::perf::operation_counter<int, std::uint64_t>;

constexpr auto to_op_counter = [](auto i) { return algol::perf::operation_counter<int>(i); };

template <typename T, std::size_t N, typename URBG>
void build_random_array (std::array<T, N>& arr, URBG&& gen)
{
  std::uniform_int_distribution<int> distribution(0, N);
  for (auto& v : arr)
    v = distribution(gen);
}

int main()
{
  using namespace algol::algorithms::sort;

  // Seed with a real random value, if available
  pcg_extras::seed_seq_from<std::random_device> seed_source;

  // Make a random number engine
  pcg32 rng(seed_source);

  std::array<operation_counter, 10000> array;
  build_random_array(array, rng);

  {
    std::cout << std::endl << "Bubble sort on 10000 in random order" << std::endl;
    std::array<operation_counter, 10000> arr = array;
    operation_counter::reset();
    stopwatch sw;
    fast_bubble_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "Selection sort on 10000 in random order" << std::endl;
    std::array<operation_counter, 10000> arr = array;
    operation_counter::reset();
    stopwatch sw;
    selection_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "Selection sort on 10000 in random order (STL ForwardIterator)" << std::endl;
    std::array<operation_counter, 10000> arr = array;
    operation_counter::reset();
    stopwatch sw;
    stl_selection_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "Insertion sort on 10000 in random order (BidirectionalIterartor)" << std::endl;
    std::array<operation_counter, 10000> arr = array;
    operation_counter::reset();
    stopwatch sw;
    standard_insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "Insertion sort on 10000 in random order (STL ForwardIterartor)" << std::endl;
    std::array<operation_counter, 10000> arr = array;
    operation_counter::reset();
    stopwatch sw;
    stl_insertion_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "Insertion sort on 10000 in random order (ForwardIterartor)" << std::endl;
    std::forward_list<operation_counter> lst(std::begin(array), std::end(array));
    operation_counter::reset();
    stopwatch sw;
    insertion_sort(std::begin(lst), std::end(lst));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(lst), std::end(lst)));
  }

  return 0;
}
