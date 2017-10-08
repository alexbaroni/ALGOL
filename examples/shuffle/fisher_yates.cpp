#include <iostream>
#include <array>
#include <random>
#include "algol/io/pprint.hpp"
#include "algol/algorithms/shuffle/fisher_yates.hpp"

int main()
{
  using namespace algol::algorithms::shuffle;
  std::array arr {2, 4, 6};
  std::random_device rd;
  std::mt19937 gen(rd());

  for (auto i = 0; i < 20; ++i) {
    fisher_yates_shuffle(std::begin(arr), std::end(arr), gen);
    std::cout << arr << std::endl;
  }
  std::array<int,1> arr2 {1};
  fisher_yates_shuffle(std::begin(arr2), std::end(arr2), gen);
  std::cout << arr2 << std::endl;
}
