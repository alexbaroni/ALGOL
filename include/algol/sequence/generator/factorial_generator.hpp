#ifndef ALGOL_SEQUENCE_GENERATOR_FACTORIAL_GENERATOR_HPP
#define ALGOL_SEQUENCE_GENERATOR_FACTORIAL_GENERATOR_HPP

#include "algol/sequence/sequence.hpp"

namespace algol {
  namespace sequence {
    namespace generator {
      template <typename T>
      class factorial_infinite_generator {
        mutable T current_;
        mutable T term_;

      protected:
        bool next () const
        {
          term_++;
          current_ *= term_;
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

        factorial_infinite_generator () :
            current_(T{1}), term_(T{1})
        {}
      };

      template <typename T>
      class factorial_first_n_generator {
        mutable T current_;
        mutable T term_;
        mutable std::size_t count_;

      protected:
        bool next () const
        {
          count_--;

          if (count_ <= 0)
            return false;

          term_++;
          current_ *= term_;
          return true;
        }

        T const& dereference () const
        {
          return current_;
        }

        explicit operator bool () const // any objects left?
        {
          return count_ > 0;
        }

        bool operator! () const
        {
          return count_ <= 0;
        }

        factorial_first_n_generator (std::size_t count) :
            current_(T{1}), term_(T{1}), count_ {count}
        {}
      };
    }

    template <typename T>
    using factorial_infinite_seq =
    sequence<T, generator::factorial_infinite_generator<T>>;

    template <typename T>
    using factorial_first_n_seq =
    sequence<T, generator::factorial_first_n_generator<T>>;
  }
}
#endif // ALGOL_SEQUENCE_GENERATOR_FACTORIAL_GENERATOR_HPP
