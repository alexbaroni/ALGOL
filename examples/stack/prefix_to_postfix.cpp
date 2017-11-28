#include <iostream>
#include <string>
#include <sstream>
#include "algol/eval/eval.hpp"
#include "algol/ds/stack/fixed_stack.hpp"

using namespace algol::eval;

bool is_operator (std::string const& op)
{
  return op == "+" || op == "-" || op == "*" || op == "/" || op == "^"; // || op == "%";
}

template <std::size_t N = 100>
std::string prefix_to_postfix2 (std::string const& expression)
{
  algol::ds::fixed_stack<std::string, N> stack;
  algol::ds::fixed_stack<std::string, N> token_stack;
  std::istringstream prefix {expression};

  while (!prefix.eof()) {
    std::string token;
    prefix >> token;
    token_stack.push(token);
    prefix >> std::ws;
  }

  while (!token_stack.empty()) {
    std::string token = token_stack.top();
    token_stack.pop();
    if (is_operator(token)) {
      if (stack.size() >= 2) {
        std::string operand1 = stack.top();
        stack.pop();
        std::string operand2 = stack.top();
        stack.pop();
        operand1 += ' ';
        operand1 += operand2;
        operand1 += ' ';
        operand1 += token;
        stack.push(operand1);
      }
      else {
        return algol::make_result<std::string>(make_error_code(eval_errors::invalid_prefix_expression));
      }
    }
    else {
      stack.push(token);
    }
  }
  if (stack.size() != 1)
    return algol::make_result<std::string>(make_error_code(eval_errors::invalid_prefix_expression));
  return stack.top();
}

int main ()
{
  std::string prefix = "+ * 2 3 / 6 2";
  std::string postfix = "2 3 * 6 2 / +";
  assert(prefix_to_postfix(prefix) == postfix);
  prefix = "+ - * ^ A B C D / / E F + G H";
  postfix = "A B ^ C * D - E F / G H + / +";
  assert(prefix_to_postfix(prefix) == postfix);
  prefix = "+ * 2 3 / 6 2";
  postfix = "2 3 * 6 2 / +";
  assert(prefix_to_postfix2(prefix) == postfix);
  prefix = "+ - * ^ A B C D / / E F + G H";
  postfix = "A B ^ C * D - E F / G H + / +";
  // this assert depending on system and compiler a nice or horrible message
  assert(prefix_to_postfix2(prefix) == postfix);

  return 0;
}
