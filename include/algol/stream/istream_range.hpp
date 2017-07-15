#ifndef ALGOL_STREAM_ISTREAM_RANGE_HPP
#define ALGOL_STREAM_ISTREAM_RANGE_HPP

#include <iosfwd>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/assert.hpp>

namespace algol {
  namespace stream {
    template <typename T>
    class istream_range {
      std::istream& sin_;
      mutable T obj_;

      bool next () const
      {
        sin_ >> obj_;
        return sin_ ? true : false;
      }

    public:
      // Define const_iterator and iterator together:
      using const_iterator = struct iterator
          : boost::iterator_facade<
              iterator,
              T const,
              std::input_iterator_tag
          > {
        iterator () : rng_ {}
        {}

      private:
        friend class istream_range;

        friend class boost::iterator_core_access;

        explicit iterator (istream_range const& rng)
            : rng_(rng ? &rng : nullptr)
        {}

        void increment ()
        {
          // Don't advance a singular iterator
          BOOST_ASSERT(rng_);
          // Fetch the next element, null out the
          // iterator if it fails
          if (!rng_->next())
            rng_ = nullptr;
        }

        bool equal (iterator that) const
        {
          return rng_ == that.rng_;
        }

        T const& dereference () const
        {
          // Don't dereference a singular iterator
          BOOST_ASSERT(rng_);
          return rng_->obj_;
        }

        istream_range const* rng_;
      };

      explicit istream_range (std::istream& sin)
          : sin_(sin), obj_ {}
      {
        next(); // prime the pump
      }

      iterator begin () const
      { return iterator{*this}; }

      iterator end () const
      { return iterator{}; }

      explicit operator bool () const // any objects left?
      {
        return sin_ ? true : false;
      }

      bool operator! () const
      { return !sin_; }
    };
  }
}
#endif // ALGOL_STREAM_ISTREAM_RANGE_HPP
