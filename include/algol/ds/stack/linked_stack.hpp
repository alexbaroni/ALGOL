#include "stack.hpp"

#ifndef ALGOL_DS_LINKED_STACK_HPP
#define ALGOL_DS_LINKED_STACK_HPP

namespace algol {
    namespace ds {
        template<typename T>
        class linked_stack final : public stack<T> {
        public:
            using value_type = typename stack<T>::value_type;
            using reference = typename stack<T>::reference;
            using const_reference = typename stack<T>::const_reference;
            using size_type = typename stack<T>::size_type;

            bool empty() const noexcept override {
              return top_ == nullptr;
            }

            size_type size() const noexcept override {
              return items_;
            }

            reference top() override {
              if (empty())
                throw stack_empty_error{"Attempting top() on empty stack"};

              return top_->value_;
            }

            const_reference top() const override {
              if (empty())
                throw stack_empty_error{"Attempting top() on empty stack"};

              return top_->value_;
            }

            void push(value_type const &value) override {
              push(new node{value, nullptr});
            }

            void push(value_type &&value) override {
              push(new node{std::move(value), nullptr});
            }

            void pop() override {
              if (empty())
                throw stack_empty_error{"Attempting pop() on empty stack"};

              node *node_to_pop = top_;
              top_ = top_->next_;
              items_--;
              delete node_to_pop;
            }

            std::vector<T> to_vector() override {
              std::vector<T> vector{};
              vector.reserve(size());

              node *iter = top_;

              while (iter) {
                vector.emplace_back(iter->value_);
                iter = iter->next_;
              }
              return vector;
            }

            void swap(linked_stack &rhs) noexcept {
              using std::swap;
              swap(top_, rhs.top_);
              swap(items_, rhs.items_);
            }

            linked_stack() : stack<T>(), top_{nullptr}, items_{size_type{}} {}

            linked_stack(linked_stack const &rhs) : linked_stack() {
              linked_stack stack;

              if (!rhs.empty()) {
                for (auto i = size_type{}; i < rhs.items_; ++i) {
                  stack.push(new node{T{}, nullptr});
                }

                node *iter = stack.top_;
                node *rhs_iter = rhs.top_;

                while (rhs_iter) {
                  new(&iter->value_) T(rhs_iter->value_);
                  iter = iter->next_;
                  rhs_iter = rhs_iter->next_;
                }
              }
              swap(stack);
            }

            linked_stack &operator=(linked_stack const &rhs) {
              linked_stack temp{rhs};
              swap(temp);
              return *this;
            }

            linked_stack(linked_stack &&rhs) noexcept : top_{rhs.top_}, items_{rhs.items_} {
              rhs.top_ = nullptr;
              rhs.items_ = size_type{};
            }

            linked_stack &operator=(linked_stack &&rhs) noexcept {
              linked_stack temp{std::move(rhs)};
              swap(temp);
              return *this;
            }

            ~linked_stack() {
              while (!empty()) {
                pop();
              }
            };

        private:
            struct node {
                T value_;
                node *next_;
            };

            void push(node *node_to_push) {
              node_to_push->next_ = top_;
              top_ = node_to_push;
              items_++;
            }

            node *top_;
            size_type items_;
        };

        template<typename T>
        void swap(linked_stack<T> &lhs, linked_stack<T> &rhs) noexcept {
          lhs.swap(rhs);
        }
    }
}

#endif //ALGOL_DS_LINKED_STACK_HPP
