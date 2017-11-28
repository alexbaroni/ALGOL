#ifndef ALGOL_SEQUENCE_GENERATOR_HALVING_GENERATOR_HPP
#define ALGOL_SEQUENCE_GENERATOR_HALVING_GENERATOR_HPP

#include "algol/sequence/sequence.hpp"

namespace algol::sequence {
  namespace generator {
    template <typename T>
    class halving_generator {
      mutable T current_;
    protected:
      bool next () const
      {
        current_ >>= 1;
        if (current_ <= 0)
          return false;
        return true;
      }

      T const& dereference () const
      {
        return current_;
      }

      explicit operator bool () const // any objects left?
      {
        return current_ > 0;
      }

      bool operator! () const
      {
        return current_ <= 0;
      }

      halving_generator () : current_(T{})
      {}

      halving_generator (T const& current) : current_(current)
      { current_ >>= 1; }

      halving_generator (T&& current) : current_(std::move(current))
      { current_ >>= 1; }
    };
  }

  template <typename T>
  using halving_seq =
  sequence<T, generator::halving_generator<T>>;
}

#endif //ALGOL_SEQUENCE_GENERATOR_HALVING_GENERATOR_HPP
