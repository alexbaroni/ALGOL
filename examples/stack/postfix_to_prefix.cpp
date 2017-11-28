#include <cassert>
#include <string>
#include "algol/eval/eval.hpp"

int main ()
{
  std::string prefix = "+ * 2 3 / 6 2";
  std::string postfix = "2 3 * 6 2 / +";
  assert(algol::eval::postfix_to_prefix(postfix) == prefix);
  prefix = "+ - * ^ A B C D / / E F + G H";
  postfix = "A B ^ C * D - E F / G H + / +";
  auto x = algol::eval::postfix_to_prefix(postfix);
  //assert(algol::eval::postfix_to_prefix(postfix) == prefix);
  return 0;
}
