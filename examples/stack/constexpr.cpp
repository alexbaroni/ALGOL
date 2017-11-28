#include <iostream>
#include "algol/io/pprint.hpp"
#include "algol/ds/stack/array_stack.hpp"

namespace ds = algol::ds;

template <typename T>
constexpr auto push (T i)
{

  return [i] (auto j) { return i + j; };
}

//template <typename T, std::size_t N>
//constexpr auto pop(ds::array_stack<T, N> s) {
//
//  return [s](){ s.pop(); return; };
//}

template <typename T, std::size_t N>
constexpr auto bottom_element (ds::array_stack<T, N> s)
{
  if (s.size() == 1) return s.top();
  s.pop();
  return bottom_element(s);
}

template <typename T, std::size_t N>
constexpr auto max (ds::array_stack<T, N> s)
{
  T max = T{};
  while (!std::empty(s)) {
    if (max < s.top())
      max = s.top();
    s.pop();
  }

  return max;
}

constexpr bool f ()
{
  constexpr ds::array_stack<int, 10> dstack {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  constexpr auto dstack2 {dstack};
  static_assert(dstack == dstack2);
  static_assert(dstack <= dstack2);
  static_assert(dstack >= dstack2);
  constexpr auto spop = [] (auto s) {
    s.pop();
    return s;
  };
//  constexpr auto check =[](ds::array_stack <int, 10> s) constexpr {
//    s.pop();
//    static_assert(s.top() == 8);
//    static_assert(s.size() == 9);
//    return true;
//  };

  static_assert(dstack.size() == 10);
  static_assert(!dstack.empty());
  static_assert(dstack.full());
  static_assert(dstack.top() == 9);
  static_assert(dstack2.size() == 10);
  static_assert(bottom_element(dstack2) == 0);
  static_assert(max(dstack2) == 9);
  constexpr auto dstack3 = spop(dstack2);
  static_assert(dstack3.top() == 8);
  static_assert(dstack3.size() == 9);
//  static_assert(check(dstack));
//  static_assert([](ds::array_stack <int, 10> s) constexpr {
//    s.pop();
//    static_assert(s.top() == 8);
//    static_assert(s.size() == 9);
//    return true;
//  }(dstack);
  return true;
}

int main ()
{
  constexpr ds::array_stack<int, 10> cstack;
  static_assert(cstack.size() == 0);
  static_assert(cstack.empty());
  static_assert(!cstack.full());
  //static_assert((static_cast<void>(cstack.push(1)), true), "!");

  static_assert(f());

  //constexpr auto x = dstack.pop();
//  static_assert((static_cast<void>(dstack.pop()), true), "!");

//  std::cout << dstack.to_vector() << std::endl;
  return 0;
}
