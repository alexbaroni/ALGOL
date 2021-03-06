#ifndef ALGOL_SEQUENCE_GENERATOR_IOTA_GENERATOR_HPP
#define ALGOL_SEQUENCE_GENERATOR_IOTA_GENERATOR_HPP

#include "algol/sequence/sequence.hpp"

namespace algol::sequence {
  namespace generator {
    template <typename T>
    class iota_infinite_generator {
      mutable T current_;

    protected:
      bool next () const
      {
        current_++;
        return true;
      }

      T const& dereference () const
      {
        return current_;
      }

      explicit operator bool () const // any objects left?
      {
        return true;
      }

      bool operator! () const
      {
        return false;
      }

      iota_infinite_generator () : current_(T{1})
      {}
    };

    template <typename T>
    class iota_upto_n_generator {
      mutable T current_;
      T max_;
    protected:
      bool next () const
      {
        current_++;
        if (current_ > max_)
          return false;
        return true;
      }

      T const& dereference () const
      {
        return current_;
      }

      explicit operator bool () const // any objects left?
      {
        return current_ < max_;
      }

      bool operator! () const
      {
        return current_ >= max_;
      }

      iota_upto_n_generator () : current_(T{1})
      {}

      iota_upto_n_generator (T const& max) : current_(T{1}), max_(max)
      {}

      iota_upto_n_generator (T&& max) : current_(T{1}), max_(std::move(max))
      {}
    };
  }

  template <typename T>
  using iota_infinite_seq =
  sequence<T, generator::iota_infinite_generator<T>>;

  template <typename T>
  using iota_upto_n_seq =
  sequence<T, generator::iota_upto_n_generator<T>>;
}
#endif // ALGOL_SEQUENCE_GENERATOR_IOTA_GENERATOR_HPP
