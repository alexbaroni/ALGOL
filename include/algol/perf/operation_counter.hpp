#ifndef ALGOL_PERF_OPERATION_COUNTER_HPP
#define ALGOL_PERF_OPERATION_COUNTER_HPP

#include <iostream>

namespace algol { namespace perf {
    template <typename T, typename Counter = std::uint64_t>
    class operation_counter final
    {
    public:
        typedef T value_type;
        typedef Counter counter_type;

        operation_counter() : value_{}
        { assignments_++; }

        operation_counter(T value) : value_{value}
        { assignments_++; }

        operation_counter(operation_counter const& value) : value_{value.value_}
        { assignments_++; }

        operation_counter(operation_counter&& value) : value_(std::move(value.value_))
        { moves_++; }

        operation_counter& operator=(T value)
        {
            assignments_++;
            value_ = value;
            return *this;
        }

        operation_counter& operator=(operation_counter const& value)
        {
            assignments_++;
            value_ = value.value_;
            return *this;
        }

        operation_counter& operator=(operation_counter&& value)
        {
            moves_++;
            value_ = std::move(value.value_);
            return *this;
        }

        ~operation_counter() = default;

        operator T() const
        {
            accesses_++;
            return value_;
        }

        operation_counter& operator++()
        {
            increments_++;
            ++value_;
            return *this;
        }

        operation_counter& operator--()
        {
            decrements_++;
            --value_;
            return *this;
        }

        operation_counter operator++(int)
        {
            increments_++;
            return operation_counter(value_++);
        }

        operation_counter operator--(int)
        {
            decrements_++;
            return operation_counter(value_--);
        }

        operation_counter& operator+=(T value)
        {
            additions_++;
            value_ += value;
            return *this;
        }

        operation_counter& operator+=(operation_counter value)
        {
            additions_++;
            value_ += value.value_;
            return *this;
        }

            operation_counter& operator-=(T value)
        {
            subtractions_++;
            value_ -= value;
            return *this;
        }

        operation_counter& operator*=(T value)
        {
            multiplications_++;
            value_ *= value;
            return *this;
        }

        operation_counter& operator/=(T value)
        {
            divisions_++;
            value_ /= value;
            return *this;
        }

        operation_counter& operator%=(T value)
        {
            moduli_++;
            value_ %= value;
            return *this;
        }

        operation_counter& operator&=(T value)
        {
            ands_++;
            value_ &= value;
            return *this;
        }

        operation_counter& operator|=(T value)
        {
            ors_++;
            value_ |= value;
            return *this;
        }

        operation_counter& operator^=(T value)
        {
            xors_++;
            value_ ^= value;
            return *this;
        }

        operation_counter& operator<<=(T value)
        {
            left_shifts_++;
            value_ <<= value;
            return *this;
        }

        operation_counter& operator>>=(T value)
        {
            right_shifts_++;
            value_ >>= value;
            return *this;
        }

        operation_counter operator+() const
        {
            unary_plus_++;
            return operation_counter(+value_);
        }

        operation_counter operator-() const
        {
            unary_minus_++;
            return operation_counter(-value_);
        }

        operation_counter operator!() const
        {
            nots_++;
            return operation_counter(!value_);
        }

        operation_counter operator~() const
        {
            complements_++;
            return operation_counter(~value_);
        }

        static Counter const& accesses()
        { return accesses_; }

        static Counter const& assignments()
        { return assignments_; }

        static Counter const& moves()
        { return moves_; }

        static Counter const& increments()
        { return increments_; }

        static Counter const& decrements()
        { return decrements_; }

        static Counter const& additions()
        { return additions_; }

        static Counter const& subtractions()
        { return subtractions_; }

        static Counter const& multiplications()
        { return multiplications_; }

        static Counter const& divisions()
        { return divisions_; }

        static Counter const& moduli()
        { return moduli_; }

        static Counter const& equal_comparisons()
        { return equal_comparisons_; }

        static Counter const& less_comparisons()
        { return less_comparisons_; }

        static Counter const& great_comparisons()
        { return great_comparisons_; }

        static Counter const& less_eq_comparisons()
        { return less_eq_comparisons_; }

        static Counter const& great_eq_comparisons()
        { return great_eq_comparisons_; }

        static Counter const& ands()
        { return ands_; }

        static Counter const& ors()
        { return ors_; }

        static Counter const& xors()
        { return xors_; }

        static Counter const& left_shifts()
        { return left_shifts_; }

        static Counter const& right_shifts()
        { return right_shifts_; }

        static Counter const& unary_plus()
        { return unary_plus_; }

        static Counter const& unary_minus()
        { return unary_minus_; }

        static Counter const& nots()
        { return nots_; }

        static Counter const& complements()
        { return complements_; }

        static void report(std::ostream& os)
        {
            os  << "Counter report:" << '\n'
            << " Accesses:             " << accesses_ << '\n'
            << " Assignments:          " << assignments_ << '\n'
            << " Moves:                " << moves_  << '\n'
            << " Increments:           " << increments_  << '\n'
            << " Decrements:           " << decrements_  << '\n'
            << " Additions:            " << additions_  << '\n'
            << " Subtractions:         " << subtractions_  << '\n'
            << " Multiplications:      " << multiplications_  << '\n'
            << " Divisions:            " << divisions_  << '\n'
            << " Moduli:               " << moduli_  << '\n'
            << " Equal comparisons:    " << equal_comparisons_  << '\n'
            << " Less comparisons:     " << less_comparisons_  << '\n'
            << " Great comparisons:    " << great_comparisons_  << '\n'
            << " Less eq comparisons:  " << less_eq_comparisons_  << '\n'
            << " Great eq comparisons: " << great_eq_comparisons_  << '\n'
            << " Ands:                 " << ands_ << '\n'
            << " Ors:                  " << ors_ << '\n'
            << " Xors:                 " << xors_ << '\n'
            << " Left_shifts:          " << left_shifts_ << '\n'
            << " Right_shifts:         " << right_shifts_ << '\n'
            << " Unary_plus:           " << unary_plus_ << '\n'
            << " Unary_minus:          " << unary_minus_ << '\n'
            << " Nots:                 " << nots_ << '\n'
            << " Comlements:           " << complements_ << std::endl;
        }

        static void reset(void)
        {
            accesses_ = Counter{};
            assignments_ = Counter{};
            moves_ = Counter{};
            increments_ = Counter{};
            decrements_ = Counter{};
            additions_ = Counter{};
            subtractions_ = Counter{};
            multiplications_ = Counter{};
            divisions_ = Counter{};
            moduli_ = Counter{};
            equal_comparisons_ = Counter{};
            less_comparisons_ = Counter{};
            great_comparisons_ = Counter{};
            less_eq_comparisons_ = Counter{};
            great_eq_comparisons_ = Counter{};
            ands_ = Counter{};
            ors_ = Counter{};
            xors_ = Counter{};
            left_shifts_ = Counter{};
            right_shifts_ = Counter{};
            unary_plus_ = Counter{};
            unary_minus_ = Counter{};
            nots_ = Counter{};
            complements_ = Counter{};
        }

    private:
        // generates a non-template operator... for this T and this Counter
        template<typename U>
        friend bool operator==(U const& y, operation_counter const& x)
        {
            equal_comparisons_++;
            return T(y) == x.value_;
        }

        template<typename U>
        friend bool operator==(operation_counter const& x, U const& y)
        {
            equal_comparisons_++;
            return x.value_ == T(y);
        }

        friend bool operator==(operation_counter const& x, operation_counter const& y)
        {
            equal_comparisons_++;
            return x.value_ == y.value_;
        }

        template<typename U>
        friend bool operator!=(U const& y, operation_counter const& x)
        {
            equal_comparisons_++;
            return T(y) != x.value_;
        }

        template<typename U>
        friend bool operator!=(operation_counter const& x, U const& y)
        {
            equal_comparisons_++;
            return x.value_ != T(y);
        }

        friend bool operator!=(operation_counter const& x, operation_counter const& y)
        {
            equal_comparisons_++;
            return x.value_ != y.value_;
        }

        template<typename U>
        friend bool operator<(U const& y, operation_counter const& x)
        {
            less_comparisons_++;
            return T(y) < x.value_;
        }

        template<typename U>
        friend bool operator<(operation_counter const& x, U const& y)
        {
            less_comparisons_++;
            return x.value_ < T(y);
        }

        friend bool operator<(operation_counter const& x, operation_counter const& y)
        {
            less_comparisons_++;
            return x.value_ < y.value_;
        }

        template<typename U>
        friend bool operator>(U const& y, operation_counter const& x)
        {
            great_comparisons_++;
            return  T(y) > x.value_;
        }

        template<typename U>
        friend bool operator>(operation_counter const& x, U const& y)
        {
            great_comparisons_++;
            return x.value_ > T(y);
        }

        friend bool operator>(operation_counter const& x, operation_counter const& y)
        {
            great_comparisons_++;
            return x.value_ > y.value_;
        }

        template<typename U>
        friend bool operator<=(U const& y, operation_counter const& x)
        {
            less_eq_comparisons_++;
            return T(y) <= x.value_;
        }

        template<typename U>
        friend bool operator<=(operation_counter const& x, U const& y)
        {
            less_eq_comparisons_++;
            return x.value_ <= T(y);
        }

        friend bool operator<=(operation_counter const& x, operation_counter const& y)
        {
            less_eq_comparisons_++;
            return x.value_ <= y.value_;
        }

        template<typename U>
        friend bool operator>=(U const& y, operation_counter const& x)
        {
            great_eq_comparisons_++;
            return T(y) >= x.value_;
        }

        template<typename U>
        friend bool operator>=(operation_counter const& x, U const& y)
        {
            great_eq_comparisons_++;
            return x.value_ >= T(y);
        }

        friend bool operator>=(operation_counter const& x, operation_counter const& y)
        {
            great_eq_comparisons_++;
            return x.value_ >= y.value_;
        }

        template <typename U>
        friend operation_counter operator+(operation_counter value1, U const& value2)
        {
            return value1 += value2;
        }

        template <typename U>
        friend operation_counter operator+(U const& value1, operation_counter value2)
        {
            return value2 += value1;
        }

        friend operation_counter operator+(operation_counter value1, operation_counter const& value2)
        {
            return value1 += value2;
        }

        template <typename U>
        friend operation_counter operator-(operation_counter value1, U const& value2)
        {
            return value1 -= value2;
        }

        template <typename U>
        friend operation_counter operator-(U const& value1, operation_counter const& value2)
        {
            return operation_counter(value1) -= value2;
        }

        friend operation_counter operator-(operation_counter value1, operation_counter const& value2)
        {
            return value1 -= value2;
        }

        template <typename U>
        friend operation_counter operator*(operation_counter value1, U const& value2)
        {
            return value1 *= value2;
        }

        template <typename U>
        friend operation_counter operator*(U const& value1, operation_counter value2)
        {
            return value2 *= value1;
        }

        friend operation_counter operator*(operation_counter value1, operation_counter const& value2)
        {
            return value1 *= value2;
        }

        template <typename U>
        friend operation_counter operator/(operation_counter value1, U const& value2)
        {
            return value1 /= value2;
        }

        template <typename U>
        friend operation_counter operator/(U const& value1, operation_counter const& value2)
        {
            return operation_counter(value1) /= value2;
        }

        friend operation_counter operator/(operation_counter value1, operation_counter const& value2)
        {
            return value1 /= value2;
        }

        template <typename U>
        friend operation_counter operator%(operation_counter value1, U const& value2)
        {
            return value1 %= value2;
        }

        template <typename U>
        friend operation_counter operator%(U const& value1, operation_counter const& value2)
        {
            return operation_counter(value1) %= value2;
        }

        friend operation_counter operator%(operation_counter value1, operation_counter const& value2)
        {
            return value1 %= value2;
        }

        template <typename U>
        friend operation_counter operator&(operation_counter value1, U const& value2)
        {
            return value1 &= value2;
        }

        template <typename U>
        friend operation_counter operator&(U const& value1, operation_counter const& value2)
        {
            return operation_counter(value1) &= value2;
        }

        friend operation_counter operator&(operation_counter value1, operation_counter const& value2)
        {
            return value1 &= value2;
        }

        template <typename U>
        friend operation_counter operator|(operation_counter value1, U const& value2)
        {
            return value1 |= value2;
        }

        template <typename U>
        friend operation_counter operator|(U const& value1, operation_counter const& value2)
        {
            return operation_counter(value1) |= value2;
        }

        friend operation_counter operator|(operation_counter value1, operation_counter const& value2)
        {
            return value1 |= value2;
        }

        template <typename U>
        friend operation_counter operator^(operation_counter value1, U const& value2)
        {
            return value1 ^= value2;
        }

        template <typename U>
        friend operation_counter operator^(U const& value1, operation_counter const& value2)
        {
            return operation_counter(value1) ^= value2;
        }

        friend operation_counter operator^(operation_counter value1, operation_counter const& value2)
        {
            return value1 ^= value2;
        }

        template <typename U>
        friend operation_counter operator<<(operation_counter value1, U const& value2)
        {
            return value1 <<= value2;
        }

        template <typename U>
        friend operation_counter operator<<(U const& value1, operation_counter const& value2)
        {
            return operation_counter(value1) <<= value2;
        }

        friend operation_counter operator<<(operation_counter value1, operation_counter const& value2)
        {
            return value1 <<= value2;
        }

        template <typename U>
        friend operation_counter operator>>(operation_counter value1, U const& value2)
        {
            return value1 >>= value2;
        }

        template <typename U>
        friend operation_counter operator>>(U const& value1, operation_counter const& value2)
        {
            return operation_counter(value1) >>= value2;
        }

        friend operation_counter operator>>(operation_counter value1, operation_counter const& value2)
        {
            return value1 >>= value2;
        }

        friend std::ostream& operator<<(std::ostream& os, operation_counter const& value)
        {
            return os << value.value_;
        }

        T value_;
        static Counter accesses_;
        static Counter assignments_;
        static Counter moves_;
        static Counter increments_;
        static Counter decrements_;
        static Counter additions_;
        static Counter subtractions_;
        static Counter multiplications_;
        static Counter divisions_;
        static Counter moduli_;
        static Counter equal_comparisons_;
        static Counter less_comparisons_;
        static Counter great_comparisons_;
        static Counter less_eq_comparisons_;
        static Counter great_eq_comparisons_;
        static Counter ands_;
        static Counter ors_;
        static Counter xors_;
        static Counter left_shifts_;
        static Counter right_shifts_;
        static Counter unary_plus_;
        static Counter unary_minus_;
        static Counter nots_;
        static Counter complements_;
    };

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::accesses_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::assignments_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::moves_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::increments_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::decrements_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::additions_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::subtractions_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::multiplications_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::divisions_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::moduli_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::equal_comparisons_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::less_comparisons_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::great_comparisons_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::less_eq_comparisons_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::great_eq_comparisons_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::ands_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::ors_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::xors_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::left_shifts_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::right_shifts_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::unary_plus_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::unary_minus_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::nots_ = Counter{};

    template <typename T, typename Counter>
    Counter operation_counter<T, Counter>::complements_ = Counter{};
}}

#endif //ALGOL_PERF_OPERATION_COUNTER_HPP
