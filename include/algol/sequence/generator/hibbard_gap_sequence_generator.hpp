#ifndef ALGOL_SEQUENCE_GENERATOR_HIBBARD_GAP_SEQUENCE_GENERATOR_HPP
#define ALGOL_SEQUENCE_GENERATOR_HIBBARD_GAP_SEQUENCE_GENERATOR_HPP

#include <cmath>
#include "algol/sequence/sequence.hpp"

namespace algol::sequence {
  namespace generator {
    template <typename T>
    class hibbard_gap_sequence_generator {
      static std::size_t find_first_exp_less_than (T const& value)
      {
        auto exp = std::floor(std::log2(value));
        if (std::pow(2, exp) - 1 >= value)
          --exp;
        return static_cast<std::size_t>(exp);
      }

      mutable std::size_t current_exp_;
      mutable T current_;
    protected:
      bool next () const
      {
        --current_exp_;
        if (current_exp_ == 0)
          return false;
        current_ = std::pow(2, current_exp_) - 1;
        return true;
      }

      T const& dereference () const
      {
        return current_;
      }

      explicit operator bool () const // any objects left?
      {
        return current_exp_ > 0;
      }

      bool operator! () const
      {
        return current_exp_ == 0;
      }

      hibbard_gap_sequence_generator () : current_exp_(T{})
      { current_ = T{}; }

      hibbard_gap_sequence_generator (T const& value) : current_exp_(find_first_exp_less_than(value))
      { current_ = std::pow(2, current_exp_) - 1; }

      hibbard_gap_sequence_generator (T&& value) : current_exp_(find_first_exp_less_than(std::move(value)))
      { current_ = std::pow(2, current_exp_) - 1; }
    };
  }

  template <typename T>
  using hibbard_gap_seq =
  sequence<T, generator::hibbard_gap_sequence_generator<T>>;
}
#endif //ALGOL_SEQUENCE_GENERATOR_HIBBARD_GAP_SEQUENCE_GENERATOR_HPP
