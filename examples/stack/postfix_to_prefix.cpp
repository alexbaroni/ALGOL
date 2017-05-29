#include <iostream>
#include <string>
#include "algol/eval/eval.hpp"

using namespace algol::eval;

int main() {
  std::string prefix = "+ * 2 3 / 6 2";
  std::string postfix = "2 3 * 6 2 / +";
  assert(postfix_to_prefix(postfix) == prefix);
  prefix = "+ - * ^ A B C D / / E F + G H";
  postfix = "A B ^ C * D - E F / G H + / +";
  assert(postfix_to_prefix(postfix) == prefix);
  return 0;
}
