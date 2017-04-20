#ifndef ALGOL_STREAM_LINES_RANGE_HPP
#define ALGOL_STREAM_LINES_RANGE_HPP

#include <iosfwd>
#include <string>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/assert.hpp>

namespace algol {
  namespace stream {
    class lines_range {
      std::istream& sin_;
      mutable std::string obj_;
      char delim_;

      bool next() const {
        std::getline(sin_, obj_, delim_);
        return sin_ ? true : false;
      }

    public:
      // Define const_iterator and iterator together:
      using const_iterator = struct iterator
          : boost::iterator_facade<
              iterator,
              std::string const,
              std::input_iterator_tag
          > {
        iterator() : rng_{} {}

      private:
        friend class lines_range;

        friend class boost::iterator_core_access;

        explicit iterator(lines_range const& rng)
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

        std::string const& dereference() const {
          // Don't dereference a singular iterator
          BOOST_ASSERT(rng_);
          return rng_->obj_;
        }

        lines_range const* rng_;
      };

      explicit lines_range(std::istream& sin, char delim = '\n')
          : sin_(sin), obj_{}, delim_(delim) {
        next(); // prime the pump
      }

      iterator begin() const { return iterator{*this}; }

      iterator end() const { return iterator{}; }

      explicit operator bool() const // any objects left?
      {
        return sin_ ? true : false;
      }

      bool operator!() const { return !sin_; }
    };

    inline
    lines_range getlines(std::istream& sin, char delim = '\n') {
      return lines_range{sin, delim};
    }
  }
}

#endif // ALGOL_STREAM_LINES_RANGE_HPP
