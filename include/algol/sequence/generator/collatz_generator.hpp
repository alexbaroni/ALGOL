#ifndef ALGOL_SEQUENCE_GENERATOR_COLLATZ_GENERATOR_HPP
#define ALGOL_SEQUENCE_GENERATOR_COLLATZ_GENERATOR_HPP

#include "algol/sequence/sequence.hpp"

namespace algol { namespace sequence {
        namespace generator {
            template<typename T>
            class collatz_generator {
                mutable T current_;
            protected:
                bool next() const {
                    if (current_ <= T{1})
                        return false;
                    current_ = current_ & 1 ? (3 * current_ + 1) : current_ >> 1;
                    return true;
                }

                T const &dereference() const {
                    return current_;
                }

                explicit operator bool() const // any objects left?
                {
                    return current_ > T{1};
                }

                bool operator!() const {
                    return current_ <= T{1};
                }

                collatz_generator() : current_(T{1}) {}
                collatz_generator(T const& current) : current_(current) {}
                collatz_generator(T&& current) : current_(std::move(current)) {}
            };
        }

        template<typename T>
        using collatz_seq =
        sequence<T, generator::collatz_generator<T>>;
    }}
#endif // ALGOL_SEQUENCE_GENERATOR_COLLATZ_GENERATOR_HPP
