#ifndef ALGOL_SEQUENCE_SEQUENCE_HPP
#define ALGOL_SEQUENCE_SEQUENCE_HPP

#include <iostream>
#include <iosfwd>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/assert.hpp>

namespace algol {
  namespace sequence {
    template<typename T, typename Generator>
    class sequence : private Generator {
    public:
      // Define const_iterator and iterator together:
      using const_iterator = struct iterator
          : boost::iterator_facade<
              iterator,
              T const,
              boost::forward_traversal_tag,
              T const&,
              T
          > {
        iterator() : seq_{} {}

      private:
        friend class sequence;

        friend class boost::iterator_core_access;

        explicit iterator(sequence const& seq)
            : seq_(seq ? &seq : nullptr) {}

        void increment() {
          // Don't advance a singular iterator
          BOOST_ASSERT(seq_);
          // Fetch the next element, null out the
          // iterator if it fails
          if (!seq_->next())
            seq_ = nullptr;
        }

        bool equal(iterator that) const {
          return seq_ == that.seq_;
        }

        T const& dereference() const {
          // Don't dereference a singular iterator
          BOOST_ASSERT(seq_);
          return seq_->dereference();
        }

        sequence const* seq_;
      };

      template<typename... Args>
      explicit sequence(Args&& ... args) : Generator(std::forward<Args>(args)...) {}

      iterator begin() const { return iterator{*this}; }

      iterator end() const { return iterator{}; }
    };
  }
}
#endif // ALGOL_SEQUENCE_SEQUENCE_HPP
