/**
 * \file
 * Array stack implementation.
 */

#ifndef ALGOL_DS_ARRAY_STACK_HPP
#define ALGOL_DS_ARRAY_STACK_HPP

#include <algorithm>
#include <array>
#include <type_traits>
#include "stack.hpp"
#include "stl2/concepts.hpp"

namespace algol::ds {
  namespace concepts = std::experimental::ranges;

  /**
   * \brief Implementation of the Stsck ADT using a std::array
   * \details A stack is a sequence that can be accessed in <b>'last-in, first-out' (LIFO) order</b>
   * The only accessible item is the one that was most recently added (pushed).
   * The preconditions of the operations are enforced, postconditions and invariant aren't enforced.
   * \tparam T type of the items stored in the stack.
   * \invariant The item that is accessible at the top of the stack is the item that has
   * most recently been pushed onto it and not yet popped (removed).
   */
  template <concepts::CopyConstructible T, std::size_t N>
  class array_stack final {
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
    constexpr bool empty () const
    {
      return items_ == size_type{0};
    }

    /**
     * \brief The stack is full?
     * \precondition None
     * \postcondition Stack is not changed
     * \complexity O(1)
     * \return True if the stack is full, false otherwise
     */
    constexpr bool full () const
    {
      return top_item_ == N;
    }

    /**
     * \brief The size of the stack
     * \precondition None
     * \postcondition Stack is not changed
     * \complexity O(1)
     * \return The current number of the items on the stack
     */
    constexpr size_type size () const
    {
      return items_;
    }

    /**
     * \brief A reference at the item on the top of the stack
     * \precondition The stack is not empty
     * \postcondition Stack is not changed
     * \complexity O(1)
     * \throws stack_empty_error if the stack is empty
     * \return The item on the top of the stack
     */
    constexpr reference top () &
    {
      if (empty())
        throw stack_empty_error{"Attempting top() on empty stack"};

      return array_[top_item_ - 1];
    }

    /**
     * \brief A constant reference at the item on the top of the stack
     * \precondition The stack is not empty
     * \postcondition Stack is not changed
     * \complexity O(1)
     * \throws stack_empty_error if the stack is empty
     * \return The item on the top of the stack
     */
    constexpr const_reference top () const&
    {
      if (empty())
        throw stack_empty_error{"Attempting top() on empty stack"};

      return array_[top_item_ - 1];
    }

    /**
     * \brief Push the item passed onto the stack
     * \precondition The stack is not full
     * \postcondition The size of the Stack is increased by 1 and the item passed becomes the current top
     * \complexity O(1)
     * \throws stack_full_error if the stack is full and the stack is not changed
     * \param value The item to push onto the stack
     */
    constexpr void push (value_type const& value)
    {
      if (full())
        throw stack_full_error{"Attempting push() on full stack"};

      array_[top_item_] = value;
      top_item_++;
      items_++;
    }

    /**
     * \brief Push the item passed onto the stack
     * \precondition The stack is not full
     * \postcondition The size of the Stack is increased by 1 and the item passed becomes the current top
     * \complexity O(1)
     * \throws stack_full_error if the stack is full and the stack is not changed
     * \param value The item to push onto the stack with move operation
     */
    constexpr void push (value_type&& value)
    {
      if (full())
        throw stack_full_error{"Attempting push() on full stack"};

      array_[top_item_] = std::move(value);
      top_item_++;
      items_++;
    }

    /**
     * \brief Pop the current top item from the stack
     * \precondition The stack is not empty
     * \postcondition The size of the Stack is decreased by 1 and the current top item is removed from the stack
     * \complexity O(1)
     * \throws stack_empty_error if the stack is empty
     */
    constexpr void pop ()
    {
      if (empty())
        throw stack_empty_error{"Attempting pop() on empty stack"};

      top_item_--;
      items_--;
    }

    /**
     * \brief Clear the stack removing all the items
     * \details Invalidates any references or pointers referring to contained elements
     * \precondition None
     * \postcondition The stack is empty, the size becomes 0
     * \complexity O(1)
     */
    constexpr void clear ()
    {
      items_ = size_type{0};
      top_item_ = size_type{0};
    }

    /**
     * \brief Creates a vector with the items pushed onto the stack
     * \precondition None
     * \postcondition The stack is unchanged
     * \complexity O(N)
     * \return A vector with the items pushed onto the stack
     */
    std::vector<value_type> to_vector () const
    {
      std::vector<value_type> vector {};
      vector.reserve(size());

      for (auto i = items_; i > size_type{0}; --i) {
        vector.emplace_back(array_[i - 1]);
      }
      return vector;
    }

    /**
     * \brief Default constructor
     * \precondition None
     * \postcondition The stack is empty
     * \complexity O(1)
     */
    constexpr array_stack ()
      noexcept (std::is_nothrow_default_constructible_v<value_type> && noexcept(size_type{0}))
        : items_{size_type{0}}, top_item_{size_type{0}}, array_{}
    {}

    /**
     * \brief Construct a stack with values provided
     * \details The values are pushed onto the stack starting at begin of initializer list and stopping at the end
     * If the initializer_list contains {1, 2, 3, 4} the stack will contains [4, 3, 2, 1]
     * \precondition None
     * \postcondition The stack size is the same of the initializer_list and all the items contained in the
     * initializer_list are pushed onto the stack
     * \complexity O(N)
     * \param values The items to be pushed onto the stack
     */
    constexpr array_stack (std::initializer_list<value_type> values) : array_stack ()
    {
      for (auto const& v : values)
        push(v);
    }

    /**
     * \brief Copy constructor
     * \precondition None
     * \postcondition This stack is equal to the provided stack
     * \complexity O(N)
     * \param rhs The stack to be copied
     */
    array_stack (array_stack const&) = default;

    /**
     * \brief Move constructor
     * \precondition None
     * \postcondition This stack is equal to the provided stack that becomes empty
     * \complexity O(N) moving std:array is O(N)
     * \param rhs The stack to be moved, items contained are 'stolen' from this stack
     */
    array_stack (array_stack&&) = default;

    /**
     * \brief Assignment operator
     * \details The actual items of the stack are destroyed and are replaced with the items of the provided stack
     * \precondition None
     * \postcondition This stack is equal to the provided stack
     * \complexity O(N)
     * \param rhs The stack to be copied
     * \return The stack containing the provided stack items
     */
    array_stack& operator= (array_stack const&) = default;

    /**
     * \brief Move assignment operator
     * \details The actual items of the stack are destroyed and are replaced with the items of the provided stack
     * \precondition None
     * \postcondition This stack is equal to the provided stack that becomes empty
     * \complexity O(N) moving std:array is O(N)
     * \param rhs The stack to be moved, items contained are 'stolen' from this stack
     * \return The stack containing the provided stack items
     */
    array_stack& operator= (array_stack&&) = default;

    /**
     * \brief Destructor
     * \precondition None
     * \postcondition The stack items are destroyed
     * \complexity O(N) Destructor calls (for std::array elements)
     */
    ~array_stack () = default;

    /**
     * \brief Equality operator
     * \details It must be reflexive, symmetric and transitive
     * \precondition None
     * \postcondition The stack is unchanged
     * \complexity O(N)
     * \param rhs The stack to be compared with this
     * \return True if the items are the same and in the same order, false otherwise
     */

    constexpr bool operator== (array_stack const& rhs) const
    requires concepts::EqualityComparable<T>
    {
      if (items_ != rhs.items_)
        return false;

      for (auto i = size_type{0}; i < items_; ++i) {
        if (array_[i] != rhs.array_[i])
          return false;
      }

      return true;
    }

    /**
     * \brief Inequality operator
     * \details Implemented in terms of equality operator
     * \precondition None
     * \postcondition The stack is unchanged
     * \complexity O(N)
     * \param rhs The stack to be compared with this
     * \return True if the items are not the same or not in the same order, false otherwise
     */

    constexpr bool operator!= (array_stack const& rhs) const
    requires concepts::EqualityComparable<T>
    {
      return !(*this == rhs);
    }

    /**
     * \brief Less than operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two stacks are compared element by element
     * - The first mismatching item defines which stacks is lexicographically less or greater than the other
     * - If one stack is a prefix of another, the shorter stack is lexicographically less than the other
     * - If two stacks have equivalent elements and are of the same length, then the stacks are lexicographically equal
     * - An empty stack is lexicographically less than any non-empty stack
     * - Two empty stacks are lexicographically equal
     * \precondition None
     * \postcondition The stack is unchanged
     * \complexity O(N)
     * \param rhs The stack to be compared with this
     * \return True if this stack is lexicographically less than the provided stack, false otherwise
     */
    constexpr bool operator< (array_stack const& rhs) const
    requires concepts::StrictTotallyOrdered<T>
    {
      auto items = std::min(items_, rhs.items_);
      for (auto i = size_type{0}; i < items; ++i) {
        if (array_[i] < rhs.array_[i])
          return true;

        if (array_[i] > rhs.array_[i])
          return false;
      }

      return items_ < rhs.items_;
    }

    /**
     * \brief Less than or equal operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two stacks are compared element by element
     * - The first mismatching item defines which stacks is lexicographically less or greater than the other
     * - If one stack is a prefix of another, the shorter stack is lexicographically less than the other
     * - If two stacks have equivalent elements and are of the same length, then the stacks are lexicographically equal
     * - An empty stack is lexicographically less than any non-empty stack
     * - Two empty stacks are lexicographically equal
     * \precondition None
     * \postcondition The stack is unchanged
     * \complexity O(N)
     * \param rhs The stack to be compared with this
     * \return True if this stack is lexicographically less than or equal to the provided stack, false otherwise
     */
    constexpr  bool operator<= (array_stack const& rhs) const
    requires concepts::StrictTotallyOrdered<T>
    {
      return !(*this > rhs);
    }

    /**
     * \brief Greater than operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two stacks are compared element by element
     * - The first mismatching item defines which stacks is lexicographically less or greater than the other
     * - If one stack is a prefix of another, the shorter stack is lexicographically less than the other
     * - If two stacks have equivalent elements and are of the same length, then the stacks are lexicographically equal
     * - An empty stack is lexicographically less than any non-empty stack
     * - Two empty stacks are lexicographically equal
     * \precondition None
     * \postcondition The stack is unchanged
     * \complexity O(N)
     * \param rhs The stack to be compared with this
     * \return True if this stack is lexicographically greater than the provided stack, false otherwise
     */
    constexpr bool operator> (array_stack const& rhs) const
    requires concepts::StrictTotallyOrdered<T>
    {
      return rhs < *this;
    }

    /**
     * \brief Greater than or equal operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two stacks are compared element by element
     * - The first mismatching item defines which stacks is lexicographically less or greater than the other
     * - If one stack is a prefix of another, the shorter stack is lexicographically less than the other
     * - If two stacks have equivalent elements and are of the same length, then the stacks are lexicographically equal
     * - An empty stack is lexicographically less than any non-empty stack
     * - Two empty stacks are lexicographically equal
     * \precondition None
     * \postcondition The stack is unchanged
     * \complexity O(N)
     * \param rhs The stack to be compared with this
     * \return True if this stack is lexicographically greater than or equal to the provided stack, false otherwise
     */
    constexpr bool operator>= (array_stack const& rhs) const
    requires concepts::StrictTotallyOrdered<T>
    {
      return !(*this < rhs);
    }

    /**
     * \brief Swaps the items of this stack with the items of the provided stack
     * \details noexcept operation, it cannot throw
     * \precondition None
     * \postcondition This stack becomes the rhs stack and viceversa
     * \complexity O(N) std::array swap is O(N)
     * \param rhs The stack to be swapped with this
     */
    void swap (array_stack& rhs) noexcept(std::is_nothrow_swappable_v<value_type>)
    {
      using std::swap;
      swap(items_, rhs.items_);
      swap(top_item_, rhs.top_item_);
      swap(array_, rhs.array_);
    }

  private:
    size_type items_;
    size_type top_item_;
    std::array<value_type, N> array_;
  };

  /**
   * \brief Exchanges the items of lhs and rhs stacks
   * \details Non member function, noexcept it cannot fail
   * \tparam T type of the items stored in the stack
   * \precondition None
   * \postcondition The lhs stack becomes the rhs stack and viceversa
   * \complexity O(N)
   * \param lhs Stack to be exchanged with rhs
   * \param rhs Stack to be exchanged with lhs
   */
  template <typename T, typename stack<T>::size_type N>
  void swap (array_stack<T, N>& lhs, array_stack<T, N>& rhs) noexcept(noexcept(lhs.swap(rhs)))
  {
    lhs.swap(rhs);
  }
}

#endif //ALGOL_DS_ARRAY_STACK_HPP
