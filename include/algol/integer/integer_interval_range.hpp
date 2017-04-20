#ifndef ALGOL_INTEGER_INTEGER_INTERVAL_RANGE_HPP
#define ALGOL_INTEGER_INTEGER_INTERVAL_RANGE_HPP

#include <iosfwd>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/assert.hpp>

#include "integer_interval.hpp"

namespace algol {
  namespace integer {
    template <typename T>
    class integer_interval_range
    {
      integer_interval <T>& interval_;
      mutable T obj_;

      bool next() const {
        if (empty(interval_) || obj_ >= upper(interval_))
          return false;

        ++obj_;

        return true;
      }
    public:
      typedef T base_type;

      // Define const_iterator and iterator together:
      using const_iterator = struct iterator
          : boost::iterator_facade<
              iterator,
              T const,
              boost::forward_traversal_tag,
              T const&,
              T
          >
      {
        iterator() : rng_ {} {}
      private:
        friend class integer_interval_range;

        friend class boost::iterator_core_access;

        explicit iterator(integer_interval_range const& rng)
            : rng_(rng ? &rng : nullptr) {}

        void increment() {
          // Don't advance a singular iterator
          BOOST_ASSERT(rng_);
          // Fetch the next element, null out the
          // iterator if it fails
          if (!rng_->next())
            rng_ = nullptr;
        }

        bool equal(iterator that) const {
          return rng_ == that.rng_;
        }

        T const& dereference() const {
          // Don't dereference a singular iterator
          BOOST_ASSERT(rng_);
          return rng_->obj_;
        }

        integer_interval_range const* rng_;
      };

      explicit integer_interval_range(integer_interval <T>& interval)
          : interval_(interval), obj_(lower(interval)) {
      }

      iterator begin() const { return iterator{*this}; }
      iterator end() const { return iterator{}; }

      explicit operator bool() const // any objects left?
      {
        return !empty(interval_) && obj_ < upper(interval_);
      }

      bool operator!() const { return empty(interval_) || obj_ >= upper(interval_); }
    };
  }
}
#endif // ALGOL_INTEGER_INTEGER_INTERVAL_RANGE_HPP