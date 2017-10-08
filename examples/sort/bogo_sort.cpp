#include <iostream>
#include <array>
#include <iterator>
#include <cassert>
#include <algorithm>
#include "algol/io/pprint.hpp"
#include "algol/perf/stopwatch.hpp"
#include "algol/perf/operation_counter.hpp"
#include "algol/algorithms/sort/bogo_sort.hpp"

int main()
{
  using namespace algol::algorithms::sort;
  using stopwatch = algol::perf::stopwatch<std::chrono::microseconds>;
  using operation_counter = algol::perf::operation_counter<int, std::uint64_t>;

  std::cout << "Random bogo sort" << std::endl;
  {
    std::cout << std::endl << "5 elements:" << std::endl;
    std::array<operation_counter, 5> arr {-2, 5, 4, -3, 6};
    operation_counter::reset();
    stopwatch sw;
    random_bogo_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "6 elements:" << std::endl;
    std::array<operation_counter, 6> arr {-2, 5, 4, -3, 6, 1};
    operation_counter::reset();
    stopwatch sw;
    random_bogo_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "10 elements:" << std::endl;
    std::array<operation_counter, 10> arr {-2, 5, 4, -3, 6, 1, 3, 2, 9, 7};
    operation_counter::reset();
    stopwatch sw;
    random_bogo_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  std::cout << std::endl << "Deterministic bogo sort" << std::endl;
  {
    std::cout << std::endl << "5 elements:" << std::endl;
    std::array<operation_counter, 5> arr {-2, 5, 4, -3, 6};
    operation_counter::reset();
    stopwatch sw;
    deterministic_bogo_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "6 elements:" << std::endl;
    std::array<operation_counter, 6> arr {-2, 5, 4, -3, 6, 1};
    operation_counter::reset();
    stopwatch sw;
    deterministic_bogo_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  {
    std::cout << std::endl << "10 elements:" << std::endl;
    std::array<operation_counter, 10> arr {-2, 5, 4, -3, 6, 1, 3, 2, 9, 7};
    operation_counter::reset();
    stopwatch sw;
    deterministic_bogo_sort(std::begin(arr), std::end(arr));
    std::cout << sw;
    std::cout << "< " << operation_counter::less_comparisons() << " swaps " << operation_counter::swaps() << std::endl;
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
  }

  return 0;
}

