#include <iostream>
#include <cmath>
#include <cassert>
#include <system_error>  // bring in std::error_code et al
#include "algol/math/math.hpp"
#include "algol/eval/eval.hpp"


int main() {
  double val;
  std::string expression = "2 3 4 + *";
  val = algol::eval::evaluate_postfix<double>(expression);
  assert(algol::math::nearly_equal(val, 14.0));

  expression = "7 3 12 + - ";
  val = algol::eval::evaluate_postfix<double>(expression);
  assert(algol::math::nearly_equal(val, -8.0));

  expression = "7 3 12 - -5 * + ";
  val = algol::eval::evaluate_postfix<double>(expression);
  assert(algol::math::nearly_equal(val, 52.0));

  expression = "7 3 + 12 - -5 1 * +";
  val = algol::eval::evaluate_postfix<double>(expression);
  assert(algol::math::nearly_equal(val, -7.0));

  expression = "2 3 2 ^ *";
  val = algol::eval::evaluate_postfix<double>(expression);
  assert(algol::math::nearly_equal(val, 18.0));

  expression = "2 3 * 6 2 / +";
  val = algol::eval::evaluate_postfix<double>(expression);
  assert(algol::math::nearly_equal(val, 9.0));

  try {
    expression = "7 3 12 + ";
    val = algol::eval::evaluate_postfix<double>(expression); //throws invalid_postfix_expression
  }
  catch(std::system_error const& e) {
    std::cout << e.code().category().name() << ": " << e.what() << std::endl;
  }

  return 0;
}