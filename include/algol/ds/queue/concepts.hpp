#ifndef ALGOL_DS_QUEUE_CONCEPTS_HPP
#define ALGOL_DS_QUEUE_CONCEPTS_HPP

#include "stl2/concepts.hpp"

namespace algol::concepts {
  template <typename S>
  concept bool Queue ()
  {
    return requires(Q
    queue, typename Q::value_type const&value) {
      typename Q::value_type;
      typename Q::size_type;
      typename Q::reference;
      typename Q::const_reference;
      { queue.empty() } -> bool;
      { queue.full() } -> bool;
      { queue.size() } ->  typename Q::size_type;
      { queue.front() } ->  typename Q::const_reference;
      queue.enqueue(value);
      queue.dequeue();
      queue.clear();
    };
  }
}
#endif //ALGOL_DS_QUEUE_CONCEPTS_HPP
