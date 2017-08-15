#ifndef ALGOL_ALGORITHMS_STACK_SORT_HPP
#define ALGOL_ALGORITHMS_STACK_SORT_HPP

#include <iterator>
#include <functional>
#include "algol/ds/stack/concepts.hpp"

namespace algol::algorithms::stack {
  /**
   * \brief Sorts a stack using (optimized?) insertion sort algorithm
   * \details Uses temporary stack to store the elements popped from input stack
   * \tparam S A container implementing the Stack concept
   * \precondition None
   * \postcondition The input stack becomes sorted in the order specified by the compare functor passed
   * \complexity O(N^2)
   * \param stack The stack to sort
   * \return None
   */
  template<algol::concepts::Stack S, typename Compare = std::less<typename S::value_type>,
      typename = std::enable_if_t<std::is_move_assignable_v<S>>>
  void stack_sort (S& stack, Compare comp = Compare{})
  {
    S temp_stack;

    // we consider the maximum instead of minimum because we are dealing with stacks and
    // we have to push the greatest elements first

    while (!std::empty(stack)) {
      // loop invariant (holds also at the end of this loop)
      // stack + temp_stack is a permutation of the input stack it has the same elements in different order
      // the elements in temp_stack are in correct order

      // element to move to temporary stack in position according to compare functor
      auto value = stack.top();
      stack.pop();

      // The loop that follow are the specific behavior of Insertion sort
      // it makes room for inserting the value in the correct position
      // move the elements in position that are <= than the element to sort,
      // according to compare functor, from the temporary stack into the input stack
      while (!std::empty(temp_stack) && comp(temp_stack.top(), value)) {
        // loop invariant (holds also at the end of this loop)
        // stack + value + temp_stack is a permutation of the input stack it has the same elements in different order
        stack.push(temp_stack.top());
        temp_stack.pop();
      }
      // push the element in position onto temporary stack
      temp_stack.push(value);
    }
    // loop postcondition
    // the input stack is empty and temp_stack is a permutation of the input stack
    // it has the same elements in sorted order
    stack = std::move(temp_stack);
  }

  /**
   * \brief Sorts a stack using insertion sort algorithm
   * \details Uses temporary stack to store the elements popped from input stack
   * \tparam S A container implementing the Stack concept
   * \precondition None
   * \postcondition The input stack becomes sorted in the order specified by the compare functor passed
   * \complexity O(N^2)
   * \param stack The stack to sort
   * \return None
   */
  template<algol::concepts::Stack S, typename Compare = std::less<typename S::value_type>>
  void insertion_sort (S& stack, Compare comp = Compare{})
  {
    S temp_stack{};
    auto sorted = typename S::size_type{1};

    // we consider the maximum instead of minimum because we are dealing with stacks and
    // we have to push the greatest elements first

    while(sorted <= std::size(stack)) {
      // loop invariant (holds also at the end of this loop)
      // stack is a permutation of the input stack it has the same elements in different order
      // starting from bottom of the stack there are (sorted - 1) elements in the correct order

      // element to move to input stack in position according to compare functor
      auto value = stack.top();
      stack.pop();

      // The 2 loops that follow are the specific behavior of Insertion sort
      // they make room for inserting the value in the correct position

      // move the unsorted elements of the input stack onto the temporary stack
      while (std::size(stack) >= sorted) {
        temp_stack.push(stack.top());
        stack.pop();
      }

      // move the sorted elements of the input stack that are <= than the element to sort
      // onto the temporary stack
      while (!std::empty(stack) && comp(stack.top(), value)) {
        temp_stack.push(stack.top());
        stack.pop();
      }

      stack.push(value);

      // move the sorted elements that are <= than value and he unsorted elements
      // from the temporary stack onto the input stack
      while (!std::empty(temp_stack)) {
        stack.push(temp_stack.top());
        temp_stack.pop();
      }
      // inner loop postcondition
      // starting from bottom of the stack there are sorted elements in the correct order

      // this and the above loop restore the outer loop invariant
      ++sorted;
    }
    // postcondition
    // stack is a permutation of the input stack it has the same elements in different order
    // starting from bottom of the stack there are stack.size sorted elements
  }

  /**
   * \brief Sorts a stack using selection sort algorithm
   * \details Uses temporary stack to store the elements popped from input stack
   * \tparam S A container implementing the Stack concept
   * \precondition None
   * \postcondition The input stack becomes sorted in the order specified by the compare functor passed.
   * \complexity O(N^2)
   * \param stack The stack to sort
   * \return None
   */
  template<algol::concepts::Stack S, typename Compare = std::less<typename S::value_type>>
  void selection_sort (S& stack, Compare comp = Compare{})
  {
    S temp_stack{};
    auto sorted = typename S::size_type{1};

    // we consider the maximum instead of minimum because we are dealing with stacks and
    // we have to push the greatest elements first

    while(sorted < std::size(stack)) {
      // loop invariant (holds also at the end of this loop)
      // stack is a permutation of the input stack it has the same elements in different order
      // starting from bottom of the stack there are (sorted - 1) elements in the correct order

      // element to start the search for maximum element in the unsorted part
      auto value = stack.top();
      stack.pop();

      // find the maximum element in the unsorted elements of the input stack and push the others
      // onto the temporary stack
      // this is the specific behavior of Selection sort
      while (std::size(stack) >= sorted) {
        // loop invariant (holds also at the end of this loop)
        // value is maximum element in the unsorted part of the input stack scanned so far
        if (comp(stack.top(), value)) {
          temp_stack.push(stack.top());
          stack.pop();
        }
        else {
          temp_stack.push(value);
          value = stack.top();
          stack.pop();
        }
      }
      // inner loop postcondition
      // here value is <= every sorted element and value >= every unsorted element

      // push the maximum element of the unsorted part in the right position of the input stack
      stack.push(value);

      // move the unsorted elements from the temporary stack onto the input stack
      // this restore the outer loop invariant
      while (!std::empty(temp_stack)) {
        stack.push(temp_stack.top());
        temp_stack.pop();
      }

      ++sorted;
    }
    // postcondition
    // stack is a permutation of the input stack it has the same elements in different order
    // starting from bottom of the stack there are stack.size sorted elements
  }
}
#endif //ALGOL_ALGORITHMS_STACK_SORT_HPP
