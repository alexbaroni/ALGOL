#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cassert>
#include "algol/ds/stack/fixed_stack.hpp"

const std::set<char> open_delim {'{', '[', '('};
const std::map<char, char> close_delim = {{'}', '{'},
                                          {']', '['},
                                          {')', '('}};

bool is_balanced (std::string const& text)
{
  auto open_end = std::end(open_delim);
  auto close_end = std::end(close_delim);
  algol::ds::fixed_stack<char, 100> stack;

  for (const auto& c : text) {
    if (auto open = open_delim.find(c); open != open_end) {
      stack.push(c);
    }
    else {
      if (auto close = close_delim.find(c); close != close_end) {
        if (stack.empty())
          return false;

        if (auto& delim = close->second; stack.top() != delim)
          return false;
        stack.pop();
      }
    }
  }

  return stack.empty();
}

int main ()
{
  std::string unbalanced = "abc{d[ef()]dd]00[]}";
  assert(!is_balanced(unbalanced));
  std::string balanced = "abc{d[ef()]dd}00[]";
  assert(is_balanced(balanced));
  unbalanced = "x{{yz}}}";
  assert(!is_balanced(unbalanced));
  unbalanced = "{x{y{{z}}}";
  assert(!is_balanced(unbalanced));
  balanced = "{{{x}}}";
  assert(is_balanced(balanced));
  balanced = "{ab(c[d])e}";
  assert(is_balanced(balanced));
  unbalanced = "{ab(c))";
  assert(!is_balanced(unbalanced));
}
