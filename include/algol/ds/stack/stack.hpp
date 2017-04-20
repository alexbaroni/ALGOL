#ifndef ALGOL_DS_STACK_HPP
#define ALGOL_DS_STACK_HPP

#include <vector>
#include <stdexcept>

namespace algol {
  namespace ds {
    struct stack_error : public virtual std::logic_error {
#if defined(__clang__)
      using std::logic_error::logic_error;
#else

      explicit stack_error(std::string const& what_arg) : std::logic_error{what_arg} {}

#endif
    };

    struct stack_empty_error : public stack_error {
      explicit stack_empty_error(std::string const& what_arg) : std::logic_error{what_arg},
                                                                stack_error{what_arg} {}
    };

    struct stack_full_error : public stack_error {
      explicit stack_full_error(std::string const& what_arg) : std::logic_error{what_arg},
                                                               stack_error{what_arg} {}
    };

    template<typename T>
    class stack {
    public:
      using value_type = T;
      using reference = value_type&;
      using const_reference = value_type const&;
      using size_type = std::size_t;

      bool empty() const {
        return empty_();
      };

      bool full() const {
        return full_();
      };

      size_type size() const {
        return size_();
      }

      reference top() {
        if (empty_())
          throw stack_empty_error{"Attempting top() on empty stack"};

        return top_();
      }

      const_reference top() const {
        if (empty_())
          throw stack_empty_error{"Attempting top() on empty stack"};

        return top_();
      }

      void push(value_type const& value) {
        if (full_())
          throw stack_full_error{"Attempting push() on full stack"};

        push_(value);
      }

      void push(value_type&& value) {
        if (full_())
          throw stack_full_error{"Attempting push() on full stack"};

        push_(std::forward<value_type>(value));
      }

      void pop() {
        if (empty_())
          throw stack_empty_error{"Attempting pop() on empty stack"};

        pop_();
      }

      std::vector<T> to_vector() const {
        return to_vector_();
      };

      stack() = default;
      stack(stack const&) = default;
      stack& operator=(stack const&) = default;
      stack(stack&&) = default;
      stack& operator=(stack&&) = default;
      virtual ~stack() = default;

    private:
      virtual bool empty_() const noexcept = 0;
      virtual bool full_() const noexcept = 0;
      virtual size_type size_() const noexcept = 0;
      virtual reference top_() = 0;
      virtual const_reference top_() const = 0;
      virtual void push_(value_type const& value) = 0;
      virtual void push_(value_type&& value) = 0;
      virtual void pop_() = 0;
      virtual std::vector<T> to_vector_() const = 0;
    };
  }
}
#endif //ALGOL_DS_STACK_HPP
