#include <iostream>
#include <cmath>
#include <cassert>
#include <system_error>  // bring in std::error_code et al
#include "algol/eval/eval.hpp"

using namespace algol::eval;

bool is_equal (double a, double b, double epsilon)
{
  return std::abs(a - b) < epsilon;
}

int main ()
{
  double val;
  std::string expression = "2 3 4 + *";
  val = evaluate_postfix<double>(expression);
  assert(is_equal(val, 14.0, 0.0000001));

  expression = "7 3 12 + - ";
  val = evaluate_postfix<double>(expression);
  assert(is_equal(val, -8.0, 0.0000001));

  expression = "7 3 12 - -5 * + ";
  val = evaluate_postfix<double>(expression);
  assert(is_equal(val, 52.0, 0.0000001));

  expression = "7 3 + 12 - -5 1 * +";
  val = evaluate_postfix<double>(expression);
  assert(is_equal(val, -7.0, 0.0000001));

  expression = "2 3 2 ^ *";
  val = evaluate_postfix<double>(expression);
  assert(is_equal(val, 18.0, 0.0000001));

  expression = "2 3 * 6 2 / +";
  val = evaluate_postfix<double>(expression);
  assert(is_equal(val, 9.0, 0.0000001));

  try {
    expression = "7 3 12 + ";
    val = evaluate_postfix<double>(expression); //throws invalid_postfix_expression
  }
  catch (std::system_error const& e) {
    std::cout << e.code().category().name() << ": " << e.what() << std::endl;
  }

  return 0;
}