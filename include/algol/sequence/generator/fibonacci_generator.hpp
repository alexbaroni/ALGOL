#ifndef ALGOL_SEQUENCE_GENERATOR_FIBONACCI_GENERATOR_HPP
#define ALGOL_SEQUENCE_GENERATOR_FIBONACCI_GENERATOR_HPP

#include "algol/sequence/sequence.hpp"

namespace algol { namespace sequence {
    namespace generator {
        template<typename T>
        class fibonacci_infinite_generator {
            mutable T current_;
            mutable T next_;

        protected:
            bool next() const {
                T next = current_ + next_;
                current_ = next_;
                next_ = next;
                return true;
            }

            T const &dereference() const {
                return next_;
            }

            explicit operator bool() const // any objects left?
            {
                return true;
            }

            bool operator!() const {
                return false;
            }

            fibonacci_infinite_generator() : current_(T{0}), next_(T{1}) {}
        };

        template<typename T, std::size_t Max>
        class fibonacci_upto_n_generator {
            mutable T current_;
            mutable T next_;
        protected:
            bool next() const {
                T next = current_ + next_;
                if (next > Max)
                    return false;
                current_ = next_;
                next_ = next;
                return true;
            }

            T const &dereference() const {
                return next_;
            }

            explicit operator bool() const // any objects left?
            {
                return Max > (current_ + next_);
            }

            bool operator!() const {
                return Max <= (current_ + next_);;
            }

            fibonacci_upto_n_generator() : current_(T{0}), next_(T{1}) {}
        };

        template<typename T, std::size_t Count>
        class fibonacci_first_n_generator {
            mutable T current_;
            mutable T next_;
            mutable std::size_t count_;

        protected:
            bool next() const {
                count_++;

                if (count_ >= Count)
                    return false;

                T next = current_ + next_;
                current_ = next_;
                next_ = next;
                return true;
            }

            T const &dereference() const {
                return next_;
            }

            explicit operator bool() const // any objects left?
            {
                return count_ < Count;
            }

            bool operator!() const {
                return count_ >= Count;
            }

            fibonacci_first_n_generator() : current_(T{0}), next_(T{1}), count_{0} {}
        };

        template<typename T>
        class even_fibonacci_infinite_generator {
            mutable T current_;
            mutable T next_;

        protected:
            bool next() const {
                T next = (next_ << 2) + current_;
                current_ = next_;
                next_ = next;
                return true;
            }

            T const &dereference() const {
                return next_;
            }

            explicit operator bool() const // any objects left?
            {
                return true;
            }

            bool operator!() const {
                return false;
            }

            even_fibonacci_infinite_generator() : current_(T{0}), next_(T{2}) {}
        };
    }

    template<typename T>
    using fibonacci_infinite_seq =
    sequence<T, generator::fibonacci_infinite_generator<T>>;

    template<typename T, std::size_t N>
    using fibonacci_upto_n_seq =
    sequence<T, generator::fibonacci_upto_n_generator<T, N>>;

    template<typename T, std::size_t Count>
    using fibonacci_first_n_seq =
    sequence<T, generator::fibonacci_first_n_generator<T, Count>>;

    template<typename T>
    using even_fibonacci_infinite_seq =
    sequence<T, generator::even_fibonacci_infinite_generator<T>>;
}}
#endif // ALGOL_SEQUENCE_GENERATOR_FIBONACCI_GENERATOR_HPP
