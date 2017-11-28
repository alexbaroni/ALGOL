/**
 * \file
 * Stack ADT
 */

#ifndef ALGOL_DS_STACK_HPP
#define ALGOL_DS_STACK_HPP

#include <vector>
#include <stdexcept>

namespace algol::ds {
  /**
   * \brief Base stack exception.
   * \details Can be used to catch every stack exceptions.
   */
  struct stack_error : public virtual std::logic_error {
#if defined(__clang__)
    using std::logic_error::logic_error;
#else

    explicit stack_error (std::string const& what_arg) : std::logic_error {what_arg}
    {}

#endif
  };

  /**
   * \brief Throwed when the stack is empty.
   * \details Throwed from top and pop operation.
   */
  struct stack_empty_error : public stack_error {
    explicit stack_empty_error (std::string const& what_arg) : std::logic_error {what_arg},
                                                               stack_error {what_arg}
    {}
  };

  /**
   * \brief Throwed when the stack is full.
   * \details Throwed from push operation.
   */
  struct stack_full_error : public stack_error {
    explicit stack_full_error (std::string const& what_arg) : std::logic_error {what_arg},
                                                              stack_error {what_arg}
    {}
  };

  /**
   * \brief Stack ADT interface
   * \details A stack is a sequence that can be accessed in <b>'last-in, first-out' (LIFO) order</b>
   * The only accessible item is the one that was most recently added (pushed).
   * The preconditions of the operations are enforced, postconditions and invariant aren't enforced.
   * \tparam T type of the items stored in the stack.
   * \invariant The item that is accessible at the top of the stack is the item that has
   * most recently been pushed onto it and not yet popped (removed).
   */
  template <typename T>
  class stack {
  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;
    using size_type = std::size_t;

    /**
     * \brief The stack is empty?
     * \precondition None
     * \postcondition Stack is not changed
     * \complexity O(1)
     * \return True if the stack is empty, false otherwise
     */
    bool empty () const
    {
      return empty_();
    };

    /**
     * \brief The stack is full?
     * \precondition None
     * \postcondition Stack is not changed
     * \complexity O(1)
     * \return True if the stack is full, false otherwise
     */
    bool full () const
    {
      return full_();
    };

    /**
     * \brief The size of the stack
     * \precondition None
     * \postcondition Stack is not changed
     * \complexity O(1)
     * \return The current number of the items on the stack
     */
    size_type size () const
    {
      return size_();
    }

    /**
     * \brief A constant reference at the item on the top of the stack
     * \precondition The stack is not empty
     * \postcondition Stack is not changed
     * \complexity O(1)
     * \throws stack_empty_error if the stack is empty
     * \return The item on the top of the stack
     */
    const_reference top () const&
    {
      if (empty_())
        throw stack_empty_error{"Attempting top() on empty stack"};

      return top_();
    }

    /**
     * \brief Push the item passed onto the stack
     * \precondition The stack is not full
     * \postcondition The size of the Stack is increased by 1 and the item passed becomes the current top
     * \complexity O(1)
     * \throws stack_full_error if the stack is full and the stack is not changed
     * \param value The item to push onto the stack
     */
    void push (value_type const& value)
    {
      if (full_())
        throw stack_full_error{"Attempting push() on full stack"};

      push_(value);
    }

    /**
     * \brief Push the item passed onto the stack
     * \precondition The stack is not full
     * \postcondition The size of the Stack is increased by 1 and the item passed becomes the current top
     * \complexity O(1)
     * \throws stack_full_error if the stack is full and the stack is not changed
     * \param value The item to push onto the stack with move operation
     */
    void push (value_type&& value)
    {
      if (full_())
        throw stack_full_error{"Attempting push() on full stack"};

      push_(std::forward<value_type>(value));
    }

    /**
     * \brief Pop the current top item from the stack
     * \precondition The stack is not empty
     * \postcondition The size of the Stack is decreased by 1 and the current top item is removed from the stack
     * \complexity O(1)
     * \throws stack_empty_error if the stack is empty
     */
    void pop ()
    {
      if (empty_())
        throw stack_empty_error{"Attempting pop() on empty stack"};

      pop_();
    }

    /**
     * \brief Clear the stack removing all the items
     * \details Invalidates any references or pointers referring to contained elements
     * \precondition None
     * \postcondition The stack is empty, the size becomes 0
     * \complexity O(1) or O(N) depends on the implementation
     */
    void clear ()
    {
      clear_();
    }

    /**
     * \brief Creates a vector with the items pushed onto the stack
     * \precondition None
     * \postcondition The stack is unchanged
     * \complexity O(N)
     * \return A vector with the items pushed onto the stack
     */
    std::vector<T> to_vector () const
    {
      return to_vector_();
    };

    stack () = default;
    stack (stack const&) = default;
    stack (stack&&) = default;
    stack& operator= (stack const&) = default;
    stack& operator= (stack&&) = default;
    virtual ~stack () = default;

  private:
    virtual bool empty_ () const = 0;
    virtual bool full_ () const = 0;
    virtual size_type size_ () const = 0;
    virtual const_reference top_ () const& = 0;
    virtual void push_ (value_type const& value) = 0;
    virtual void push_ (value_type&& value) = 0;
    virtual void pop_ () = 0;
    virtual void clear_ () = 0;
    virtual std::vector<T> to_vector_ () const = 0;
  };
}
#endif //ALGOL_DS_STACK_HPP
