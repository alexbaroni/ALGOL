#include <iostream>
#include <array>
#include <utility>
#include <cassert>
#include <random>
#include "algol/algorithms/stack/sort.hpp"
#include "algol/ds/array/array.hpp"
#include "algol/ds/stack/fixed_stack.hpp"
#include "algol/func/function.hpp"
#include "algol/io/pprint.hpp"
#include "algol/perf/benchmark.hpp"

const size_t N = 100;
const size_t M = N * 20;

std::array<std::size_t, N> array_n = algol::ds::fill_array<N>(algol::identity);
std::array<std::size_t, M> array_m = algol::ds::fill_array<M>(algol::identity);

std::array<std::size_t, N> rarray_n{};
std::array<std::size_t, M> rarray_m{};

std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<std::size_t> dis(100, 999);

using benchmark = algol::perf::benchmark<std::chrono::microseconds>;

void fill_rarray()
{
  for(auto& v : rarray_n) {
    v = dis(gen);
  }

  for(auto& v : rarray_m) {
    v = dis(gen);
  }
}

void fn()
{
  algol::ds::fixed_stack<std::size_t, N> stack;
  for(const auto& v : array_n)
    stack.push(N - v);

  assert(stack.top() == 1);
  algol::algorithms::stack::insertion_sort(stack);
}

void fm()
{
  algol::ds::fixed_stack<std::size_t, M> stack;
  for(const auto& v : array_m)
    stack.push(M - v);

  assert(stack.top() == 1);
  algol::algorithms::stack::insertion_sort(stack);
}

void fnr()
{
  algol::ds::fixed_stack<std::size_t, N> stack;
  for(const auto& v : rarray_n)
    stack.push(v);

  algol::algorithms::stack::insertion_sort(stack);
}

void fmr()
{
  algol::ds::fixed_stack<std::size_t, M> stack;
  for(const auto& v : rarray_m)
    stack.push(v);

  algol::algorithms::stack::insertion_sort(stack);
}

void gn()
{
  algol::ds::fixed_stack<std::size_t, N> stack;
  for(const auto& v : array_n)
    stack.push(N - v);

  assert(stack.top() == 1);
  algol::algorithms::stack::selection_sort(stack);
}

void gm()
{
  algol::ds::fixed_stack<std::size_t, M> stack;
  for(const auto& v : array_m)
    stack.push(M - v);

  assert(stack.top() == 1);
  algol::algorithms::stack::selection_sort(stack);
}

void gnr()
{
  algol::ds::fixed_stack<std::size_t, N> stack;
  for(const auto& v : rarray_n)
    stack.push(v);

  algol::algorithms::stack::selection_sort(stack);
}

void gmr()
{
  algol::ds::fixed_stack<std::size_t, M> stack;
  for(const auto& v : rarray_m)
    stack.push(v);

  algol::algorithms::stack::selection_sort(stack);
}

void hnr()
{
  algol::ds::fixed_stack<std::size_t, N> stack;
  for(const auto& v : rarray_n)
    stack.push(v);

  algol::algorithms::stack::stack_sort(stack);
}

void hmr()
{
  algol::ds::fixed_stack<std::size_t, M> stack;
  for(const auto& v : rarray_m)
    stack.push(v);

  algol::algorithms::stack::stack_sort(stack);
}

void ins_sort()
{
  algol::ds::fixed_stack<std::size_t, N> stack{2,4,3,5,6,1};
  assert(stack.top() == 1);
  std::cout << stack.to_vector() << std::endl;
  algol::algorithms::stack::insertion_sort(stack);
  assert(std::size(stack) == 6);
  std::cout << stack.to_vector() << std::endl;

  stack.clear();
  for(const auto& v : array_n)
    stack.push(N - v);

  assert(stack.top() == 1);
  auto sort = [&stack]() { algol::algorithms::stack::insertion_sort(stack); };
  auto r1 = benchmark::run(sort);
  std::cout << "One run: " << r1;
  assert(std::size(stack) == 100);
  stack.clear();
  for(const auto& v : array_n)
    stack.push(N - v);
  algol::algorithms::stack::insertion_sort(stack);
  std::cout << stack.to_vector() << std::endl;

  auto result = benchmark::run_n(100, fn);
  assert(result.size() == 100);
  auto average_n = benchmark::run_average(result);
  std::cout << "Input size: " << N << " " << average_n;
  result = benchmark::run_n(100, fm);
  assert(result.size() == 100);
  auto average_m = benchmark::run_average(result);
  std::cout << "Input size: " << M << " " << average_m;

  auto ratio = average_m.duration / average_n.duration;
  std::cout << "Input size ratio: " << M/N << ", average execution ratio: " << ratio << std::endl;
}

void ins_sort_r()
{
  algol::ds::fixed_stack<std::size_t, N> stack{};
  for(const auto& v : rarray_n)
    stack.push(v);

  auto sort = [&stack]() { algol::algorithms::stack::insertion_sort(stack); };
  auto r1 = benchmark::run(sort);
  std::cout << "One run: " << r1;
  assert(std::size(stack) == 100);
  std::cout << stack.to_vector() << std::endl;

  auto result = benchmark::run_n(100, fnr);
  assert(result.size() == 100);
  auto average_n = benchmark::run_average(result);
  std::cout << "Input size: " << N << " " << average_n;
  result = benchmark::run_n(100, fmr);
  assert(result.size() == 100);
  auto average_m = benchmark::run_average(result);
  std::cout << "Input size: " << M << " " << average_m;

  auto ratio = average_m.duration / average_n.duration;
  std::cout << "Input size ratio: " << M/N << ", average execution ratio: " << ratio << std::endl;
}

void sel_sort()
{
  algol::ds::fixed_stack<std::size_t, N> stack {2, 4, 3, 5, 6, 1};
  assert(stack.top() == 1);
  std::cout << stack.to_vector() << std::endl;
  algol::algorithms::stack::selection_sort(stack);
  assert(std::size(stack) == 6);
  std::cout << stack.to_vector() << std::endl;

  stack = {2, 4, 3, 5, 6, 1};
  algol::algorithms::stack::selection_sort(stack, std::greater<std::size_t>{});
  assert(std::size(stack) == 6);
  std::cout << stack.to_vector() << std::endl;

  stack.clear();
  for(const auto& v : array_n)
    stack.push(N - v);

  assert(stack.top() == 1);
  auto sort = [&stack]() { algol::algorithms::stack::selection_sort(stack); };
  auto r1 = benchmark::run(sort);
  std::cout << "One run: " << r1;
  assert(std::size(stack) == 100);
  stack.clear();
  for(const auto& v : array_n)
    stack.push(N - v);
  algol::algorithms::stack::selection_sort(stack);
  std::cout << stack.to_vector() << std::endl;

  auto result = benchmark::run_n(100, gn);
  assert(result.size() == 100);
  auto average_n = benchmark::run_average(result);
  std::cout << "Input size: " << N << " " << average_n;
  result = benchmark::run_n(100, gm);
  assert(result.size() == 100);
  auto average_m = benchmark::run_average(result);
  std::cout << "Input size: " << M << " " << average_m;

  auto ratio = average_m.duration / average_n.duration;
  std::cout << "Input size ratio: " << M/N << ", average execution ratio: " << ratio;
}

void sel_sort_r()
{
  algol::ds::fixed_stack<std::size_t, N> stack {};
  for(const auto& v : rarray_n)
    stack.push(v);

  auto sort = [&stack]() { algol::algorithms::stack::selection_sort(stack); };
  auto r1 = benchmark::run(sort);
  std::cout << "One run: " << r1;
  assert(std::size(stack) == 100);
  std::cout << stack.to_vector() << std::endl;

  auto result = benchmark::run_n(100, gnr);
  assert(result.size() == 100);
  auto average_n = benchmark::run_average(result);
  std::cout << "Input size: " << N << " " << average_n;
  result = benchmark::run_n(100, gmr);
  assert(result.size() == 100);
  auto average_m = benchmark::run_average(result);
  std::cout << "Input size: " << M << " " << average_m;

  auto ratio = average_m.duration / average_n.duration;
  std::cout << "Input size ratio: " << M/N << ", average execution ratio: " << ratio;
}


void stk_sort_r()
{
  algol::ds::fixed_stack<std::size_t, N> stack{};
  for(const auto& v : rarray_n)
    stack.push(v);

  auto sort = [&stack]() { algol::algorithms::stack::stack_sort(stack); };
  auto r1 = benchmark::run(sort);
  std::cout << "One run: " << r1;
  assert(std::size(stack) == 100);
  std::cout << stack.to_vector() << std::endl;

  auto result = benchmark::run_n(100, hnr);
  assert(result.size() == 100);
  auto average_n = benchmark::run_average(result);
  std::cout << "Input size: " << N << " " << average_n;
  result = benchmark::run_n(100, hmr);
  assert(result.size() == 100);
  auto average_m = benchmark::run_average(result);
  std::cout << "Input size: " << M << " " << average_m;

  auto ratio = average_m.duration / average_n.duration;
  std::cout << "Input size ratio: " << M/N << ", average execution ratio: " << ratio << std::endl;
}

int main() {
  fill_rarray();
  std::cout << "Insertion sort" << std::endl;
  ins_sort();
  std::cout << std::endl;
  std::cout << "Selection sort" << std::endl;
  sel_sort();
  std::cout << std::endl;
  std::cout << "Insertion sort random values" << std::endl;
  ins_sort_r();
  std::cout << std::endl;
  std::cout << "Selection sort random values" << std::endl;
  sel_sort_r();
  std::cout << std::endl;
  std::cout << "Stack sort random values" << std::endl;
  stk_sort_r();

  return 0;
}
