#include <iostream>
#include <iomanip>
#include <algol/perf/operation_counter.hpp>
#include "algol/algorithms/recursion/factorial.hpp"
#include "../utility/utility.hpp"

int main ()
{
  using namespace algol::algorithms::recursion;
  using operation_counter = algol::perf::operation_counter<long double, std::uint64_t>;
  std::array<int, factorial(4)> a {};
  a[23] = -1;
  auto x = factorial(test_numeric_udt{5});
  std::cout << std::fixed << x.value() << std::endl;
  auto y = factorial(test_convertible_to_numeric_udt{5});
  std::cout << std::fixed << y << std::endl;
  std::cout << std::boolalpha << std::is_arithmetic_v<operation_counter::value_type> << std::endl;
  std::cout << std::fixed << factorial < long double > (120) << std::endl
                                                             //            << factorial(false) //compile time error
                                                             //            << factorial<algol::perf::operation_counter<bool>>(false) //compile time error
                                                             << factorial(10) << std::endl;
  //constexpr auto f = factorial<int>(-1); //compile time error
  //auto f = factorial(-6); // throw at runtime
  //std::cout << f <<  std::endl;
  std::cout << std::fixed << factorial < operation_counter > (5) << std::endl;
  std::cout << std::fixed << factorial(algol::perf::operation_counter<int>{5}) << std::endl;
  std::cout << "Closed form of factorial = 2n+1 so for fact(5) we expect 11 operation"
            << " 10 for * and - and 1 for base case" << std::endl;
  std::cout << "n of * " << operation_counter::multiplications()
            << " n of - " << operation_counter::subtractions() << std::endl;
  // this will likely overflow the stack
  // std::cout << factorial<long double>(105000) << std::endl;
  return 0;
}