#include "stack.hpp"

#ifndef ALGOL_DS_LINKED_STACK_HPP
#define ALGOL_DS_LINKED_STACK_HPP

namespace algol {
  namespace ds {
    template <typename T>
    class linked_stack final : public stack<T>
    {
    public:
      using value_type = typename stack<T>::value_type;
      using reference = typename stack<T>::reference;
      using const_reference = typename stack<T>::const_reference;
      using size_type = typename stack<T>::size_type;

      linked_stack() : stack<T>(), top_node_ {nullptr}, items_ {size_type{}} {}

      linked_stack(linked_stack const& rhs) : linked_stack() {
        linked_stack stack;

        if (!rhs.empty()) {
          for (auto i = size_type{}; i < rhs.items_; ++i) {
            stack.push_(new node {T{}, nullptr});
          }

          node* iter = stack.top_node_;
          node* rhs_iter = rhs.top_node_;

          while (rhs_iter) {
            new(&iter->value_) T(rhs_iter->value_);
            iter = iter->next_;
            rhs_iter = rhs_iter->next_;
          }
        }
        swap(stack);
      }

      linked_stack& operator=(linked_stack const& rhs) {
        linked_stack temp {rhs};
        swap(temp);
        return *this;
      }

      linked_stack(linked_stack&& rhs) noexcept : top_node_ {rhs.top_node_}, items_ {rhs.items_} {
        rhs.top_node_ = nullptr;
        rhs.items_ = size_type{};
      }

      linked_stack& operator=(linked_stack&& rhs) noexcept {
        linked_stack temp {std::move(rhs)};
        swap(temp);
        return *this;
      }

      ~linked_stack() {
        while (!empty_()) {
          pop_();
        }
      };

      void swap(linked_stack& rhs) noexcept {
        using std::swap;
        swap(top_node_, rhs.top_node_);
        swap(items_, rhs.items_);
      }

    private:
      struct node
      {
        T value_;
        node* next_;
      };

      bool empty_() const noexcept override {
        return top_node_ == nullptr;
      }

      bool full_() const noexcept override {
        return false;
      }

      size_type size_() const noexcept override {
        return items_;
      }

      reference top_() override {
        return top_node_->value_;
      }

      const_reference top_() const override {
        return top_node_->value_;
      }

      void push_(value_type const& value) override {
        push_(new node {value, nullptr});
      }

      void push_(value_type&& value) override {
        push_(new node {std::move(value), nullptr});
      }

      void pop_() override {
        node* node_to_pop = top_node_;
        top_node_ = top_node_->next_;
        items_--;
        delete node_to_pop;
      }

      std::vector<T> to_vector_() const override {
        std::vector<T> vector {};
        vector.reserve(size_());

        node* iter = top_node_;

        while (iter) {
          vector.emplace_back(iter->value_);
          iter = iter->next_;
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

    template <typename T>
    void swap(linked_stack<T>& lhs, linked_stack<T>& rhs) noexcept {
      lhs.swap(rhs);
    }
  }
}

#endif //ALGOL_DS_LINKED_STACK_HPP
