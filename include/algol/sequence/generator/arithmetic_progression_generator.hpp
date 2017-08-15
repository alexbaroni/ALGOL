#ifndef ALGOL_SEQUENCE_GENERATOR_ARITHMETIC_PROGRESSION_GENERATOR_HPP
#define ALGOL_SEQUENCE_GENERATOR_ARITHMETIC_PROGRESSION_GENERATOR_HPP

#include "algol/sequence/sequence.hpp"

namespace algol::sequence {
  namespace generator {
    template <typename T>
    class arithmetic_progression_infinite_generator {
      mutable T current_;
      T difference_;

    protected:
      bool next () const
      {
        current_ += difference_;
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

      arithmetic_progression_infinite_generator (T const& initial_term, T const& difference) :
          current_(initial_term), difference_(difference)
      {}
    };

    template <typename T>
    class arithmetic_progression_first_n_generator {
      mutable T current_;
      T difference_;
      mutable std::size_t count_;

    protected:
      bool next () const
      {
        count_--;

        if (count_ <= 0)
          return false;

        current_ += difference_;
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

      arithmetic_progression_first_n_generator (T const& initial_term, T const& difference, std::size_t count) :
          current_ {initial_term}, difference_ {difference}, count_ {count}
      {}
    };
  }

  template <typename T>
  using arithmetic_progression_infinite_seq =
  sequence<T, generator::arithmetic_progression_infinite_generator<T>>;

  template <typename T>
  using arithmetic_progression_first_n_seq =
  sequence<T, generator::arithmetic_progression_first_n_generator<T>>;
}
#endif // ALGOL_SEQUENCE_GENERATOR_ARITHMETIC_PROGRESSION_GENERATOR_HPP
