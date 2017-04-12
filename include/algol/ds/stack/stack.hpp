#ifndef ALGOL_DS_STACK_HPP
#define ALGOL_DS_STACK_HPP

#include <stdexcept>

namespace algol { namespace ds {
    struct stack_error : public virtual std::logic_error {
#if defined(__clang__)
        using std::logic_error::logic_error;
#else
        explicit stack_error(std::string const& what_arg) : std::logic_error{what_arg} {}
#endif
    };

    struct stack_empty_error : public stack_error {
        explicit stack_empty_error(std::string const& what_arg) : std::logic_error{what_arg}, stack_error{what_arg} {}
    };

    struct stack_full_error : public stack_error {
        explicit stack_full_error(std::string const& what_arg) : std::logic_error{what_arg}, stack_error{what_arg} {}
    };

    template<typename T>
    class stack {
    public:
        using value_type = T;
        using reference = value_type&;
        using const_reference = value_type const&;
        using size_type = std::size_t;

        virtual bool empty() const noexcept = 0;
        virtual size_type size() const noexcept = 0;
        virtual reference top() = 0;
        virtual const_reference top() const = 0;
        virtual void push(value_type const& value) = 0;
        virtual void push(value_type&& value) = 0;
        virtual void pop() = 0;

        stack() = default;
        stack(stack const&) = default;
        stack& operator=(stack const&) = default;
        stack(stack&&) = default;
        stack& operator=(stack&&) = default;
        virtual ~stack() = default;
    };
}}
#endif //ALGOL_DS_STACK_HPP
