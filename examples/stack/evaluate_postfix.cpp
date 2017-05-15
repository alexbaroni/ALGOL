#include <iostream>
#include <sstream>
#include <cmath>
#include <set>
#include <limits>
#include <cassert>
#include "algol/ds/stack/fixed_stack.hpp"

// Only evaluates expression with numbers and +,-,*,/
double evaluate(std::string const& expression) {
  std::set<char> operators = {'+', '-', '*', '/'};
  algol::ds::fixed_stack<double, 100> stack;
  std::istringstream in_stream{expression};

  while(!in_stream.eof()) {
    char op;
    double operand;
    in_stream >> operand;

    if(in_stream) {
      stack.push(operand);
    }
    else {
      in_stream.clear();
      in_stream.unget();
      in_stream >> op;

      if (in_stream) {
        if (operators.find(op) != std::end(operators)) {
          if(stack.size() >= 2) {
            double operand2 = stack.top();
            stack.pop();
            double operand1 = stack.top();
            stack.pop();

            switch (op) {
              case '+':
                stack.push(operand1 + operand2);
                break;
              case '-':
                stack.push(operand1 - operand2);
                break;
              case '*':
                stack.push(operand1 * operand2);
                break;
              case '/':
                stack.push(operand1 / operand2);
                break;
            }
          }
          else {
            // Malformed postfix expression missing operand
            return std::numeric_limits<double>::quiet_NaN();
          }
        }
        else {
          // Malformed postfix expression not suppoerted operator
          return std::numeric_limits<double>::quiet_NaN();
        }
      }
      else {
        // Malformed postfix expression
        return std::numeric_limits<double>::quiet_NaN();
      }
    }
    in_stream >> std::ws;
  }

  if (stack.size() != 1)
    return std::numeric_limits<double>::quiet_NaN();

  return stack.top();
}

bool is_equal(double a, double b, double epsilon) {
  return std::abs(a - b) < epsilon;
}

int main() {
  std::string expression = "2 3 4 + *";
  assert(is_equal(evaluate(expression), 14.0, 0.0000001));

  expression = "7 3 12 + - ";
  assert(is_equal(evaluate(expression), -8.0, 0.0000001));

  expression = "7 3 12 - -5 * + ";
  assert(is_equal(evaluate(expression), 52.0, 0.0000001));

  expression = "7 3 + 12 - -5 1 * +";
  assert(is_equal(evaluate(expression), -7.0, 0.0000001));
  return 0;
}