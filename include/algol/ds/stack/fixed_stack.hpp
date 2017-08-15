/**
 * \file
 * Fixed stack implementation.
 */

#ifndef ALGOL_DS_FIXED_STACK_HPP
#define ALGOL_DS_FIXED_STACK_HPP

#include <algorithm>
#include <memory>
#include "stack.hpp"
#include "stl2/concepts.hpp"

namespace algol::ds {
  using namespace ::std::experimental::ranges;

  /**
   * \brief Implementation of the Stsck ADT using a fixed array
   * \details see class [stack](@ref stack)
   * \tparam T type of the items stored in the stack
   * \invariant The item that is accessible at the top of the stack is the item that has
   * most recently been pushed onto it and not yet popped (removed)
   */
  template <CopyConstructible T, typename stack<T>::size_type N>
  class fixed_stack final : public stack<T> {
  public:
    using value_type = typename stack<T>::value_type;
    using reference = typename stack<T>::reference;
    using const_reference = typename stack<T>::const_reference;
    using size_type = typename stack<T>::size_type;

    /**
     * \brief Default constructor
     * \precondition None
     * \postcondition The stack is empty
     * \complexity O(1)
     */
    fixed_stack ()
        : stack<T>(), items_{size_type{0}}, top_item_{size_type{0}},
          array_{alloc_traits::allocate(allocator_, N)}
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
    fixed_stack (std::initializer_list<value_type> values) : fixed_stack()
    {
      for (auto const& v : values)
        push_(v);
    }

    /**
     * \brief Copy constructor
     * \precondition None
     * \postcondition This stack is equal to the provided stack
     * \complexity O(N)
     * \param rhs The stack to be copied
     */
    fixed_stack (fixed_stack const& rhs) : fixed_stack()
    {
      fixed_stack stack;

      if (!rhs.empty()) {
        for (auto i = size_type{0}; i < rhs.items_; ++i) {
          alloc_traits::construct(allocator_, std::addressof(stack.array_[i]), value_type{rhs.array_[i]});
        }

        stack.items_ = rhs.items_;
        stack.top_item_ = rhs.top_item_;
      }
      swap(stack);
    }

    /**
     * \brief Move constructor
     * \precondition None
     * \postcondition This stack is equal to the provided stack that becomes empty
     * \complexity O(1)
     * \param rhs The stack to be moved, items contained are 'stolen' from this stack
     */
    fixed_stack (fixed_stack&& rhs) noexcept : items_ {rhs.items_}, top_item_ {rhs.top_item_}, array_ {rhs.array_}
    {
      rhs.items_ = size_type{0};
      rhs.top_item_ = size_type{0};
      rhs.array_ = nullptr;
    }

    /**
     * \brief Assignment operator
     * \details The actual items of the stack are destroyed and are replaced with the items of the provided stack
     * \precondition None
     * \postcondition This stack is equal to the provided stack
     * \complexity O(N)
     * \param rhs The stack to be copied
     * \return The stack containing the provided stack items
     */
    fixed_stack& operator= (fixed_stack const& rhs)
    {
      fixed_stack temp {rhs};
      swap(temp);
      return *this;
    }

    /**
     * \brief Move assignment operator
     * \details The actual items of the stack are destroyed and are replaced with the items of the provided stack
     * \precondition None
     * \postcondition This stack is equal to the provided stack that becomes empty
     * \complexity O(1)
     * \param rhs The stack to be moved, items contained are 'stolen' from this stack
     * \return The stack containing the provided stack items
     */
    fixed_stack& operator= (fixed_stack&& rhs) noexcept
    {
      fixed_stack temp {std::move(rhs)};
      swap(temp);
      return *this;
    }

    /**
     * \brief Destructor
     * \precondition None
     * \postcondition The stack items are destroyed
     * \complexity O(N) Destructor calls
     */
    ~fixed_stack ()
    {
      for (auto i = size_type{0}; i < items_; ++i) {
        alloc_traits::destroy(allocator_, std::addressof(array_[i]));
      }
      alloc_traits::deallocate(allocator_, array_, N);
    }

    /**
     * \brief Equality operator
     * \details It must be reflexive, symmetric and transitive
     * \precondition None
     * \postcondition The stack is unchanged
     * \complexity O(N)
     * \param rhs The stack to be compared with this
     * \return True if the items are the same and in the same order, false otherwise
     */

    bool operator== (fixed_stack const& rhs) const
    requires EqualityComparable<T> ()
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

    bool operator!= (fixed_stack const& rhs) const
    requires EqualityComparable<T> ()
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
    bool operator< (fixed_stack const& rhs) const
    requires StrictTotallyOrdered<T> ()
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
    bool operator<= (fixed_stack const& rhs) const
    requires StrictTotallyOrdered<T> ()
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
    bool operator> (fixed_stack const& rhs) const
    requires StrictTotallyOrdered<T> ()
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
    bool operator>= (fixed_stack const& rhs) const
    requires StrictTotallyOrdered<T> ()
    {
      return !(*this < rhs);
    }

    /**
     * \brief Swaps the items of this stack with the items of the provided stack
     * \details noexcept operation, it cannot throw
     * \precondition None
     * \postcondition This stack becomes the rhs stack and viceversa
     * \complexity O(1)
     * \param rhs The stack to be swapped with this
     */
    void swap (fixed_stack& rhs) noexcept
    {
      using std::swap;
      swap(items_, rhs.items_);
      swap(top_item_, rhs.top_item_);
      swap(array_, rhs.array_);
    }

  private:
    bool empty_ () const final
    {
      return items_ == size_type{0};
    }

    bool full_ () const final
    {
      return top_item_ == N;
    }

    size_type size_ () const final
    {
      return items_;
    }

    reference top_ () & final
    {
      return array_[top_item_ - 1];
    }

    const_reference top_ () const& final
    {
      return array_[top_item_ - 1];
    }

    void push_ (value_type const& value) final
    {
      alloc_traits::construct(allocator_, std::addressof(array_[top_item_]), value_type{value});
      top_item_++;
      items_++;
    }

    void push_ (value_type&& value) final
    {
      alloc_traits::construct(allocator_, std::addressof(array_[top_item_]), value_type{std::move(value)});
      top_item_++;
      items_++;
    }

    void pop_ () final
    {
      top_item_--;
      items_--;
      alloc_traits::destroy(allocator_, std::addressof(array_[top_item_]));
    }

    void clear_ () final
    {
      for (auto i = size_type{0}; i < items_; ++i) {
        alloc_traits::destroy(allocator_, std::addressof(array_[i]));
      }
      items_ = size_type{0};
      top_item_ = size_type{0};
    }

    std::vector<value_type> to_vector_ () const final
    {
      std::vector<value_type> vector {};
      vector.reserve(size_());

      for (auto i = items_; i > size_type{0}; --i) {
        vector.emplace_back(array_[i - 1]);
      }
      return vector;
    }

    using alloc = std::allocator<value_type>;
    using alloc_traits = std::allocator_traits<alloc>;

    size_type items_;
    size_type top_item_;
    value_type* array_;
    alloc allocator_;
  };

  /**
   * \brief Exchanges the items of lhs and rhs stacks
   * \details Non member function, noexcept it cannot fail
   * \tparam T type of the items stored in the stack
   * \precondition None
   * \postcondition The lhs stack becomes the rhs stack and viceversa
   * \complexity O(1)
   * \param lhs Stack to be exchanged with rhs
   * \param rhs Stack to be exchanged with lhs
   */
  template <typename T, typename stack<T>::size_type N>
  void swap (fixed_stack<T, N>& lhs, fixed_stack<T, N>& rhs) noexcept
  {
    lhs.swap(rhs);
  }
}

#endif //ALGOL_DS_FIXED_STACK_HPP
