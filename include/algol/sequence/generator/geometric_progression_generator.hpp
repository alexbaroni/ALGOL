#ifndef ALGOL_SEQUENCE_GENERATOR_GEOMETRIC_PROGRESSION_GENERATOR_HPP
#define ALGOL_SEQUENCE_GENERATOR_GEOMETRIC_PROGRESSION_GENERATOR_HPP

#include "algol/sequence/sequence.hpp"

namespace algol {
  namespace sequence {
    namespace generator {
      template <typename T>
      class geometric_progression_infinite_generator {
        mutable T current_;
        T ratio_;

      protected:
        bool next () const
        {
          current_ *= ratio_;
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

        geometric_progression_infinite_generator (T const& initial_term, T const& ratio) :
            current_(initial_term), ratio_(ratio)
        {}
      };

      template <typename T>
      class geometric_progression_first_n_generator {
        mutable T current_;
        T ratio_;
        mutable std::size_t count_;

      protected:
        bool next () const
        {
          count_--;

          if (count_ <= 0)
            return false;

          current_ *= ratio_;
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

        geometric_progression_first_n_generator (T const& initial_term, T const& ratio, std::size_t count) :
            current_ {initial_term}, ratio_ {ratio}, count_ {count}
        {}
      };
    }

    template <typename T>
    using geometric_progression_infinite_seq =
    sequence<T, generator::geometric_progression_infinite_generator<T>>;

    template <typename T>
    using geometric_progression_first_n_seq =
    sequence<T, generator::geometric_progression_first_n_generator<T>>;
  }
}
#endif // ALGOL_SEQUENCE_GENERATOR_GEOMETRIC_PROGRESSION_GENERATOR_HPP
