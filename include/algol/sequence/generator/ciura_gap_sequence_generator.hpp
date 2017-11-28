#ifndef ALGOL_SEQUENCE_GENERATOR_CIURA_GAP_SEQUENCE_GENERATOR_HPP
#define ALGOL_SEQUENCE_GENERATOR_CIURA_GAP_SEQUENCE_GENERATOR_HPP

#include <array>
#include "algol/sequence/sequence.hpp"

namespace algol::sequence {
  namespace generator {
    template <typename T>
    class ciura_gap_sequence_generator {
      static constexpr std::size_t find_first_gap_less_than (T const& value)
      {
        for (std::size_t i = 0; i < std::size(gaps); ++i) {
          if (gaps[i] < value)
            return i;
        }
        return std::size(gaps) - 1;
      }

      mutable std::size_t current_;
      static constexpr std::array<T, 9> gaps {1750, 701, 301, 132, 57, 23, 10, 4, 1};
    protected:
      bool next () const
      {
        ++current_;
        if (current_ >= std::size(gaps))
          return false;
        return true;
      }

      T const& dereference () const
      {
        return gaps[current_];
      }

      explicit operator bool () const // any objects left?
      {
        return current_ < std::size(gaps);
      }

      bool operator! () const
      {
        return current_ >= std::size(gaps);
      }

      ciura_gap_sequence_generator () : current_(T{})
      {}

      ciura_gap_sequence_generator (T const& value) : current_(find_first_gap_less_than(value))
      {}

      ciura_gap_sequence_generator (T&& value) : current_(find_first_gap_less_than(std::move(value)))
      {}
    };
  }

  template <typename T>
  using ciura_gap_seq =
  sequence<T, generator::ciura_gap_sequence_generator<T>>;
}
#endif //ALGOL_SEQUENCE_GENERATOR_CIURA_GAP_SEQUENCE_GENERATOR_HPP
