/**
 * \file
 * Linked stack implementation.
 */

#include "stack.hpp"

#ifndef ALGOL_DS_LINKED_STACK_HPP
#define ALGOL_DS_LINKED_STACK_HPP

namespace algol {
  namespace ds {
    /**
     * \brief Implementation of the Stsck ADT using a linked structure.
     * \details see class [stack](@refitem stack)
     * \tparam T type of the items stored in the stack.
     * \invariant The item that is accessible at the top of the stack is the item that has
     * most recently been pushed onto it and not yet popped (removed).
     */
    template<typename T>
    class linked_stack final : public stack<T> {
    public:
      using value_type = typename stack<T>::value_type;
      using reference = typename stack<T>::reference;
      using const_reference = typename stack<T>::const_reference;
      using size_type = typename stack<T>::size_type;

      /**
       * \brief Default constructor.
       */
      linked_stack() : stack<T>(), top_node_{nullptr}, items_{size_type{}} {}

      /**
       * \brief Construct a stack with values provided.
       * \details The values are pushed onto the stack starting at begin of initializer list and stopping at the end.
       * If the initializer_list contains {1, 2, 3, 4} the stack will contains [4, 3, 2, 1].
       * \prcondition None.
       * \postcondition The stack size is the same of the initializer_list and all the items contained in the
       * initializer_list are pushed onto the stack.
       * \complexity O(N)
       * \param values The items to be pushed onto the stack.
       */
      linked_stack(std::initializer_list<T> values) : linked_stack() {
        for (auto const& v : values)
          push_(v);
      }

      /**
       * \brief Copy constructor.
       * \param rhs The stack to be copied.
       */
      linked_stack(linked_stack const& rhs) : linked_stack() {
        linked_stack stack;

        if (!rhs.empty()) {
          for (auto i = size_type{}; i < rhs.items_; ++i) {
            stack.push_(new node{T{}, nullptr});
          }

          node* this_iter = stack.top_node_;
          node* rhs_iter = rhs.top_node_;

          while (rhs_iter) {
            new(&this_iter->value_) T(rhs_iter->value_);
            this_iter = this_iter->next_;
            rhs_iter = rhs_iter->next_;
          }
        }
        swap(stack);
      }

      /**
       * \brief Assignment operator
       * \details The actual items of the stack are destroyed and are replaced with the items of the provided stack.
       * \param rhs The stack to be copied.
       * \return The stack containing the provided stack items.
       */
      linked_stack& operator=(linked_stack const& rhs) {
        linked_stack temp{rhs};
        swap(temp);
        return *this;
      }

      /**
       * \brief Move constructor.
       * \param rhs The stack to be moved, items contained are 'stolen' from this stack.
       */
      linked_stack(linked_stack&& rhs) noexcept : top_node_{rhs.top_node_}, items_{rhs.items_} {
        rhs.top_node_ = nullptr;
        rhs.items_ = size_type{};
      }

      /**
       * \brief Move assignment operator.
       * \details The actual items of the stack are destroyed and are replaced with the items of the provided stack.
       * \param rhs The stack to be moved, items contained are 'stolen' from this stack.
       * \return The stack containing the provided stack items.
       */
      linked_stack& operator=(linked_stack&& rhs) noexcept {
        linked_stack temp{std::move(rhs)};
        swap(temp);
        return *this;
      }

      /**
       * \brief Desstuctor
       */
      ~linked_stack() {
        while (!empty_()) {
          pop_();
        }
      };

      /**
       * \brief Equality operator.
       * \details It must be reflexive, symmetric and transitive.
       * \param rhs The stack to be compared with this.
       * \return True if the items are the same and in the same order, false otherwise.
       */
      bool operator==(linked_stack const& rhs) const {
        if (items_ != rhs.items_)
          return false;

        node* this_iter = top_node_;
        node* rhs_iter = rhs.top_node_;

        while (this_iter) {
          if (this_iter->value_ != rhs_iter->value_)
            return false;

          this_iter = this_iter->next_;
          rhs_iter = rhs_iter->next_;
        }

        return true;
      }

      /**
       * \brief Inequality operator.
       * \param rhs The stack to be compared with this.
       * \return True if the items are not the same or not in the same order, false otherwise.
       */
      bool operator!=(linked_stack const& rhs) const {
        return !(*this == rhs);
      }

      /**
       * \brief Less than operator.
       * \param rhs
       * \return
       */
      bool operator<(linked_stack const& rhs) const {
        node* this_iter = top_node_;
        node* rhs_iter = rhs.top_node_;

        while (this_iter && rhs_iter) {
          if (this_iter->value_ < rhs_iter->value_)
            return true;

          if (this_iter->value_ > rhs_iter->value_)
            return false;

          this_iter = this_iter->next_;
          rhs_iter = rhs_iter->next_;
        }

        return !this_iter && rhs_iter;
      }

      /**
       * \brief Less than or equal operator.
       * \param rhs
       * \return
       */
      bool operator<=(linked_stack const& rhs) const {
        return !(*this > rhs);
      }

      /**
       * \brief Greater than operator.
       * \param rhs
       * \return
       */
      bool operator>(linked_stack const& rhs) const {
        return rhs < *this;
      }

      /**
       * \brief Greater than or equal operator.
       * \param rhs
       * \return
       */
      bool operator>=(linked_stack const& rhs) const {
        return !(*this < rhs);
      }

      /**
       * \brief Swaps the items of this stack with the items of the provided items.
       * \param rhs
       */
      void swap(linked_stack& rhs) noexcept {
        using std::swap;
        swap(top_node_, rhs.top_node_);
        swap(items_, rhs.items_);
      }

    private:
      struct node {
        T value_;
        node* next_;
      };

      bool empty_() const noexcept final {
        return top_node_ == nullptr;
      }

      bool full_() const noexcept final {
        return false;
      }

      size_type size_() const noexcept final {
        return items_;
      }

      reference top_() final {
        return top_node_->value_;
      }

      const_reference top_() const final {
        return top_node_->value_;
      }

      void push_(value_type const& value) final {
        push_(new node{value, nullptr});
      }

      void push_(value_type&& value) final {
        push_(new node{std::move(value), nullptr});
      }

      void pop_() final {
        node* node_to_pop = top_node_;
        top_node_ = top_node_->next_;
        items_--;
        delete node_to_pop;
      }

      void clear_() noexcept final {
        linked_stack temp{};
        swap(temp);
      }

      std::vector<T> to_vector_() const final {
        std::vector<T> vector{};
        vector.reserve(size_());

        node* this_iter = top_node_;

        while (this_iter) {
          vector.emplace_back(this_iter->value_);
          this_iter = this_iter->next_;
        }
        return vector;
      }

      void push_(node* node_to_push) {
        node_to_push->next_ = top_node_;
        top_node_ = node_to_push;
        items_++;
      }

      node* top_node_;
      size_type items_;
    };

    template<typename T>
    void swap(linked_stack<T>& lhs, linked_stack<T>& rhs) noexcept {
      lhs.swap(rhs);
    }
  }
}

#endif //ALGOL_DS_LINKED_STACK_HPP
