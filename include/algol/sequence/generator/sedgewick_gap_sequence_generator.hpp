#ifndef ALGOL_SEQUENCE_GENERATOR_SEDGEWICK_GAP_SEQUENCE_GENERATOR_HPP
#define ALGOL_SEQUENCE_GENERATOR_SEDGEWICK_GAP_SEQUENCE_GENERATOR_HPP

#include <cmath>
#include "algol/sequence/sequence.hpp"

namespace algol::sequence {
  namespace generator {
    template <typename T>
    class sedgewick_gap_sequence_generator {
      static std::size_t find_first_exp_less_than (T const& value)
      {
        std::size_t k = 0;

        if (value <= T{8}) {
          k = 1;
        }
        else {
          do {
            ++k;
          } while ((std::pow(4, k) + 3 * std::pow(2, k - 1) + 1) < value);
        }
        return k;
      }

      mutable std::size_t current_exp_;
      mutable T current_;
    protected:
      bool next () const
      {
        --current_exp_;
        if (current_exp_ == 0)
          return false;
        if (current_exp_ == 1)
          current_ = T{1};
        else
          current_ = std::pow(4, current_exp_ - 1) + 3 * std::pow(2, current_exp_ - 2) + 1;
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

      sedgewick_gap_sequence_generator () : current_exp_(T{})
      { current_ = T{}; }

      sedgewick_gap_sequence_generator (T const& value) : current_exp_(find_first_exp_less_than(value))
      { current_ = current_exp_ == 1 ? 1 : std::pow(4, current_exp_ - 1) + 3 * std::pow(2, current_exp_ - 2) + 1; }

      sedgewick_gap_sequence_generator (T&& value) : current_exp_(find_first_exp_less_than(std::move(value)))
      { current_ = current_exp_ == 1 ? 1 : std::pow(4, current_exp_ - 1) + 3 * std::pow(2, current_exp_ - 2) + 1; }
    };
  }

  template <typename T>
  using sedgewick_gap_seq =
  sequence<T, generator::sedgewick_gap_sequence_generator<T>>;
}
#endif //ALGOL_SEQUENCE_GENERATOR_SEDGEWICK_GAP_SEQUENCE_GENERATOR_HPP
