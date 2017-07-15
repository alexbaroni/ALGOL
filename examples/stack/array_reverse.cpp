#include <array>
#include <iostream>
#include <cassert>
#include "algol/ds/stack/linked_stack.hpp"
#include "algol/perf/stopwatch.hpp"

/*
template<typename T, std::size_t N>
constexpr std::array<T, N> make_array() {
  T value{};
  std::array<T, N> values{};
  for(std::size_t i = 0; i < N; ++i) {
    values[i] = value;
    value++;
  }
  return values;
}
*/

using stopwatch = algol::perf::stopwatch<std::chrono::microseconds>;

int main ()
{
  stopwatch sw;
  //std::array<int, 10000> array = make_array<int, 10000>();
  std::array<int, 10000> array {};
  algol::ds::linked_stack<int> stack;

  for (int i = 0; i < 10000; ++i)
    array[i] = i;

  for (auto v : array)
    stack.push(v);

  assert(stack.top() == 9999);

  for (auto& v : array) {
    v = stack.top();
    stack.pop();
  }
  assert(array[0] == 9999);
  assert(array[9999] == 0);
  std::cout << sw << std::endl;
  return 0;
}