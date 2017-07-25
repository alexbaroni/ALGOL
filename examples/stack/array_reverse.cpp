#include <array>
#include <iostream>
#include <cassert>
#include "algol/func/function.hpp"
#include "algol/perf/stopwatch.hpp"
#include "algol/ds/array/array.hpp"
#include "algol/ds/stack/linked_stack.hpp"

using stopwatch = algol::perf::stopwatch<std::chrono::microseconds>;

int main() {
  stopwatch sw;
  algol::ds::linked_stack<std::size_t> stack;
  std::array<std::size_t, 10000> array = algol::ds::fill_array<10000>(algol::identity);

  for(const auto& v : array)
    stack.push(v);

  assert(stack.top() == 9999);

  for(auto& v : array) {
    v = stack.top();
    stack.pop();
  }
  assert(array[0] == 9999);
  assert(array[9999] == 0);
  std::cout << sw << std::endl;
  return 0;
}