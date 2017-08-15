#ifndef ALGOL_SEQUENCE_GENERATOR_FIBONACCI_GENERATOR_HPP
#define ALGOL_SEQUENCE_GENERATOR_FIBONACCI_GENERATOR_HPP

#include "algol/sequence/sequence.hpp"

namespace algol::sequence {
  namespace generator {
    template <typename T>
    class fibonacci_infinite_generator {
      mutable T current_;
      mutable T next_;

    protected:
      bool next () const
      {
        T next = current_ + next_;
        current_ = next_;
        next_ = next;
        return true;
      }

      T const& dereference () const
      {
        return next_;
      }

      explicit operator bool () const // any objects left?
      {
        return true;
      }

      bool operator! () const
      {
        return false;
      }

      fibonacci_infinite_generator () : current_(T{0}), next_(T{1})
      {}
    };

    template <typename T>
    class fibonacci_upto_n_generator {
      mutable T current_;
      mutable T next_;
      T max_;
    protected:
      bool next () const
      {
        T next = current_ + next_;
        if (next > max_)
          return false;
        current_ = next_;
        next_ = next;
        return true;
      }

      T const& dereference () const
      {
        return next_;
      }

      explicit operator bool () const // any objects left?
      {
        return max_ > (current_ + next_);
      }

      bool operator! () const
      {
        return max_ <= (current_ + next_);;
      }

      fibonacci_upto_n_generator () : current_(T{0}), next_(T{1}), max_(T{0})
      {}

      fibonacci_upto_n_generator (T const& max) : current_(T{0}), next_(T{1}), max_(max)
      {}

      fibonacci_upto_n_generator (T&& max) : current_(T{0}), next_(T{1}), max_(std::move(max))
      {}
    };

    template <typename T>
    class fibonacci_first_n_generator {
      mutable T current_;
      mutable T next_;
      mutable std::size_t count_;

    protected:
      bool next () const
      {
        count_--;

        if (count_ <= 0)
          return false;

        T next = current_ + next_;
        current_ = next_;
        next_ = next;
        return true;
      }

      T const& dereference () const
      {
        return next_;
      }

      explicit operator bool () const // any objects left?
      {
        return count_ > 0;
      }

      bool operator! () const
      {
        return count_ <= 0;
      }

      fibonacci_first_n_generator (std::size_t count) : current_(T{0}), next_(T{1}), count_ {count}
      {}
    };

    template <typename T>
    class even_fibonacci_infinite_generator {
      mutable T current_;
      mutable T next_;

    protected:
      bool next () const
      {
        T next = (next_ << 2) + current_;
        current_ = next_;
        next_ = next;
        return true;
      }

      T const& dereference () const
      {
        return next_;
      }

      explicit operator bool () const // any objects left?
      {
        return true;
      }

      bool operator! () const
      {
        return false;
      }

      even_fibonacci_infinite_generator () : current_(T{0}), next_(T{2})
      {}
    };

    template <typename T>
    class even_fibonacci_upto_n_generator {
      mutable T current_;
      mutable T next_;
      T max_;
    protected:
      bool next () const
      {
        T next = (next_ << 2) + current_;
        if (next > max_)
          return false;
        current_ = next_;
        next_ = next;
        return true;
      }

      T const& dereference () const
      {
        return next_;
      }

      explicit operator bool () const // any objects left?
      {
        return max_ > (next_ << 2) + current_;
      }

      bool operator! () const
      {
        return max_ <= (next_ << 2) + current_;
      }

      even_fibonacci_upto_n_generator () : current_(T{0}), next_(T{2}), max_(T{0})
      {}

      even_fibonacci_upto_n_generator (T const& max) : current_(T{0}), next_(T{2}), max_(max)
      {}

      even_fibonacci_upto_n_generator (T&& max) : current_(T{0}), next_(T{2}), max_(std::move(max))
      {}
    };

    template <typename T>
    class even_fibonacci_first_n_generator {
      mutable T current_;
      mutable T next_;
      mutable std::size_t count_;

    protected:
      bool next () const
      {
        count_--;

        if (count_ <= 0)
          return false;
        T next = (next_ << 2) + current_;
        current_ = next_;
        next_ = next;
        return true;
      }

      T const& dereference () const
      {
        return next_;
      }

      explicit operator bool () const // any objects left?
      {
        return count_ > 0;
      }

      bool operator! () const
      {
        return count_ <= 0;
      }

      even_fibonacci_first_n_generator (std::size_t count) : current_(T{0}), next_(T{2}), count_ {count}
      {}
    };
  }

  template <typename T>
  using fibonacci_infinite_seq =
  sequence<T, generator::fibonacci_infinite_generator<T>>;

  template <typename T>
  using fibonacci_upto_n_seq =
  sequence<T, generator::fibonacci_upto_n_generator<T>>;

  template <typename T>
  using fibonacci_first_n_seq =
  sequence<T, generator::fibonacci_first_n_generator<T>>;

  template <typename T>
  using even_fibonacci_infinite_seq =
  sequence<T, generator::even_fibonacci_infinite_generator<T>>;

  template <typename T>
  using even_fibonacci_upto_n_seq =
  sequence<T, generator::even_fibonacci_upto_n_generator<T>>;

  template <typename T>
  using even_fibonacci_first_n_seq =
  sequence<T, generator::even_fibonacci_first_n_generator<T>>;
}
#endif // ALGOL_SEQUENCE_GENERATOR_FIBONACCI_GENERATOR_HPP
