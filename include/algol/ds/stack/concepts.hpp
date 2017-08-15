#ifndef ALGOL_DS_STACK_CONCEPTS_HPP
#define ALGOL_DS_STACK_CONCEPTS_HPP

#include "stl2/concepts.hpp"

namespace algol::concepts {
  template <typename S>
  concept bool Stack ()
  {
    return requires(S stack, typename S::value_type const& value) {
      typename S::value_type;
      typename S::size_type;
      typename S::reference;
      typename S::const_reference;
      { stack.empty() } -> bool;
      { stack.full() } -> bool;
      { stack.size() } ->  typename S::size_type;
      { stack.top() } ->  typename S::const_reference;
      stack.push(value);
      stack.pop();
      stack.clear();
    };
  }
}
#endif //ALGOL_DS_STACK_CONCEPTS_HPP
