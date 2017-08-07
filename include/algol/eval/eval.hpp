/**
 * \file
 * Eveluation functions.
 */

#ifndef ALGOL_EVAL_EVAL_HPP
#define ALGOL_EVAL_EVAL_HPP

#include <cmath>
#include <sstream>
#include <utility>
#include <system_error>  // bring in std::error_code et al
#include "algol/math/math.hpp"
#include "algol/result/to.hpp"
#include "algol/result/result.hpp"
#include "algol/eval/eval_tokenizer.hpp"
#include "algol/ds/stack/fixed_stack.hpp"

namespace algol::eval {
  enum class eval_errors {
    invalid_prefix_expression = 1,
    invalid_postfix_expression
  };

  // This is the custom error code enum
  class eval_error : public std::error_code {
  public:
    eval_error() = default;  // Expected requires E to be default constructible
    // Only allow my construction from my enum
    inline eval_error(eval_errors c);
  };

  namespace detail {
    // Define a custom error code category derived from std::error_category
    class eval_error_category : public std::error_category {
    public:
      // Return a short descriptive name for the category
      virtual const char* name() const noexcept final { return "eval_error"; }

      // Return what each enum means in text
      virtual std::string message(int c) const final {
        switch (static_cast<eval_errors>(c)) {
          case eval_errors::invalid_prefix_expression:return "invalid prefix expression";
          case eval_errors::invalid_postfix_expression:return "invalid postfix expression";
          default:return "unknown";
        }
      }

      // OPTIONAL: Allow generic error conditions to be compared to me
      virtual std::error_condition default_error_condition(int c) const noexcept final {
        switch (static_cast<eval_errors>(c)) {
          case eval_errors::invalid_prefix_expression:
          case eval_errors::invalid_postfix_expression:return make_error_condition(std::errc::invalid_argument);
          default:
            // I have no mapping for this code
            return std::error_condition(c, *this);
        }
      }
    };
  }

  // Declare a global function returning a static instance of the custom category
  extern const detail::eval_error_category& eval_error_category() {
    static detail::eval_error_category c;
    return c;
  }

  // Now we have the custom error code category, implement the eval_error constructor
  inline eval_error::eval_error(eval_errors e) : std::error_code(static_cast<int>(e), eval_error_category()) {}

  // Overload the global make_error_code() free function with our
  // custom enum. It will be found via ADL by the compiler if needed.
  inline std::error_code make_error_code(eval_errors e) {
    return eval_error(e);
  }

  inline std::error_condition make_error_condition(eval_errors e) {
    return std::error_condition(static_cast<int>(e), detail::eval_error_category{});
  }
}

namespace std {
  // Tell the C++ 11 STL metaprogramming that enum eval_error::valid_errors
  // is registered with the standard error code system
  template<>
  struct is_error_code_enum<algol::eval::eval_errors> : std::true_type {};
}

namespace algol::eval {
  namespace detail {
    const std::string left_operand_converted = "#";

    bool is_operator(char op) {
      return op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '%';
    }

    bool is_operator(std::string const& op) {
      return op == "+" || op == "-" || op == "*" || op == "/" || op == "^" || op == "%";
    }
  }

  // Only evaluates expression with numbers and +,-,*,/,^,% separated by spaces
  template<typename T, std::size_t N = 100>
  auto evaluate_postfix(std::string const& expression) {
    algol::ds::fixed_stack<T, N> stack;
    eval_tokenizer postfix{expression};

    for (const auto& token : postfix) {
      if (detail::is_operator(token)) {
        if (stack.size() >= 2) {
          T operand2 = stack.top();
          stack.pop();
          T operand1 = stack.top();
          stack.pop();

          switch (token[0]) {
            case '+':stack.push(operand1 + operand2);
              break;
            case '-':stack.push(operand1 - operand2);
              break;
            case '*':stack.push(operand1 * operand2);
              break;
            case '/':stack.push(operand1 / operand2);
              break;
            case '%':stack.push(algol::math::mod(operand1, operand2));
              break;
            case '^':stack.push(std::pow(operand1, operand2));
              break;
          }
        }
        else {
          // Malformed postfix expression missing operand
          return algol::make_result<T>(make_error_code(eval_errors::invalid_postfix_expression));
        }
      }
      else {
        if (auto operand = algol::to<T>(token); operand.has_value()) {
          stack.push(operand);
        }
        else {
          // Malformed postfix expression (neither an operator nor an operand)
          return algol::make_result<T>(make_error_code(eval_errors::invalid_postfix_expression));
        }
      }
    }

    if (stack.size() != 1)
      return algol::make_result<T>(make_error_code(eval_errors::invalid_postfix_expression));

    return algol::make_result<T>(stack.top());
  }

  template<std::size_t N = 100>
  auto postfix_to_prefix(std::string const& expression) {
    algol::ds::fixed_stack<std::string, N> stack;
    eval_tokenizer postfix{expression};

    for (auto token : postfix) {
      if (detail::is_operator(token)) {
        if (stack.size() >= 2) {
          std::string operand2 = stack.top();
          stack.pop();
          std::string operand1 = stack.top();
          stack.pop();
          token += ' ';
          token += operand1;
          token += ' ';
          token += operand2;
          stack.push(token);
        }
        else {
          return algol::make_result<std::string>(make_error_code(eval_errors::invalid_postfix_expression));
        }
      }
      else {
        stack.push(token);
      }
    }

    if (stack.size() != 1)
      return algol::make_result<std::string>(make_error_code(eval_errors::invalid_postfix_expression));

    return algol::make_result<std::string>(stack.top());
  }

  template<std::size_t N = 100>
  auto prefix_to_postfix(std::string const& expression) {
    std::string postfix;
    eval_tokenizer prefix{expression};
    algol::ds::fixed_stack<std::string, N> stack;

    for (const auto& token : prefix) {
      if (detail::is_operator(token)) {
        stack.push(token);
      }
      else {
        if (!postfix.empty())
          postfix += ' ';
        postfix += token;

        while (!stack.empty() && stack.top() == detail::left_operand_converted) {
          stack.pop();
          if (!postfix.empty())
            postfix += ' ';
          postfix += stack.top();
          stack.pop();
        }
        stack.push(detail::left_operand_converted);
      }
    }
    return postfix;
  }
}
#endif //ALGOL_EVAL_EVAL_HPP
