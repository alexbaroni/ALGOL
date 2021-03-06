/**
 * \file
 * Eveluation tokenizer.
 */

#ifndef ALGOL_EVAL_EVAL_TOKENIZER_HPP
#define ALGOL_EVAL_EVAL_TOKENIZER_HPP

#include <string>
#include <sstream>
#include <iosfwd>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>

namespace algol::eval {
  template <typename T = std::string>
  class eval_tokenizer {
    std::istringstream iss_;
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
      friend class eval_tokenizer;

      friend class boost::iterator_core_access;

      explicit iterator (eval_tokenizer const& rng)
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

      eval_tokenizer const* rng_;
    };

    explicit eval_tokenizer (std::string const& expression)
        : iss_(std::istringstream{expression}), sin_(iss_), obj_ {}
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

#endif //ALGOL_EVAL_EVAL_TOKENIZER_HPP
