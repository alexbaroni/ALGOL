#include <vector>
#include <memory>

#include "algol/ds/stack/stack.hpp"
#include "algol/ds/stack/linked_stack.hpp"
#include "algol/perf/operation_counter.hpp"
#include "gtest/gtest.h"

namespace ds = algol::ds;

using operation_counter = algol::perf::operation_counter<std::int32_t, std::uint64_t>;

class linked_stack_fixture : public ::testing::Test {
protected:
  ds::linked_stack<operation_counter> op_count_stack;
};

TEST_F(linked_stack_fixture, axioms) {
  // Note: Axioms for the ADT stack
  // new stack is empty and not full
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_FALSE(op_count_stack.full());
  // new stack is throws stack_empty_error on pop
  EXPECT_THROW(op_count_stack.pop(), ds::stack_empty_error);
  // new stack is throws stack_empty_error on top
  EXPECT_THROW(op_count_stack.top(), ds::stack_empty_error);
  op_count_stack.push(1);
  // a stack with one item is not empty
  EXPECT_FALSE(op_count_stack.empty());
  // a stack with one item on top return that item
  EXPECT_EQ(op_count_stack.top(), 1);
  // a stack with one item does not throw on pop
  EXPECT_NO_THROW(op_count_stack.pop());
  op_count_stack.push(1);
  auto size = op_count_stack.size();
  op_count_stack.push(2);
  // a push increase the size of the stack by 1
  EXPECT_EQ(op_count_stack.size(), size + 1u);
  size = op_count_stack.size();
  op_count_stack.pop();
  // a pop decrease the size of the stack by 1
  EXPECT_EQ(op_count_stack.size(), size - 1u);
}

TEST_F(linked_stack_fixture, constructor) {
  EXPECT_FALSE(!op_count_stack.empty());
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 0u);
  EXPECT_FALSE(op_count_stack.full());
  EXPECT_TRUE(!op_count_stack.full());
}

TEST_F(linked_stack_fixture, initilizer_list) {
  std::vector<operation_counter> val = {6, 5, 4, 3, 2, 1};
  ds::linked_stack<operation_counter> init_list_stack{1, 2, 3, 4, 5, 6};
  EXPECT_FALSE(init_list_stack.empty());
  EXPECT_EQ(init_list_stack.size(), 6u);
  ASSERT_EQ(init_list_stack.to_vector(), val);
}

TEST_F(linked_stack_fixture, empty) {
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 0u);
  EXPECT_THROW(op_count_stack.pop(), ds::stack_empty_error);
  EXPECT_THROW(op_count_stack.top(), ds::stack_empty_error);
  EXPECT_THROW({ static_cast<const ds::linked_stack <operation_counter>&>(op_count_stack).top(); },
               ds::stack_empty_error);
}

TEST_F(linked_stack_fixture, one_element) {
  op_count_stack.push(2);
  EXPECT_FALSE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 1u);
  EXPECT_EQ(op_count_stack.top(), 2);
}

TEST_F(linked_stack_fixture, update_top_element) {
  op_count_stack.push(2);
  EXPECT_FALSE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 1u);
  EXPECT_EQ(op_count_stack.top(), 2);
  op_count_stack.top() = 3;
  EXPECT_EQ(op_count_stack.top(), 3);
}

TEST_F(linked_stack_fixture, swap) {
  ds::linked_stack<operation_counter> swap_stack;
  op_count_stack.push(2);
  op_count_stack.push(3);
  swap(swap_stack, op_count_stack);
  EXPECT_FALSE(swap_stack.empty());
  EXPECT_EQ(swap_stack.size(), 2u);
  EXPECT_EQ(swap_stack.top(), 3);
}

TEST_F(linked_stack_fixture, five_elements) {
  op_count_stack.push(1);
  op_count_stack.push(2);
  op_count_stack.push(3);
  op_count_stack.push(4);
  op_count_stack.push(5);
  EXPECT_FALSE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 5u);
  EXPECT_EQ(op_count_stack.top(), 5);
  op_count_stack.pop();
  EXPECT_FALSE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 4u);
  EXPECT_EQ(op_count_stack.top(), 4);
  op_count_stack.pop();
  EXPECT_FALSE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 3u);
  EXPECT_EQ(op_count_stack.top(), 3);
  op_count_stack.pop();
  EXPECT_FALSE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 2u);
  EXPECT_EQ(op_count_stack.top(), 2);
  op_count_stack.pop();
  EXPECT_FALSE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 1u);
  EXPECT_EQ(op_count_stack.top(), 1);
  op_count_stack.pop();
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 0u);
  EXPECT_THROW(op_count_stack.top(), ds::stack_empty_error);
}

TEST_F(linked_stack_fixture, big_stack) {
  for (operation_counter i = 0; i < 1000000; ++i)
    op_count_stack.push(i);
  EXPECT_EQ(op_count_stack.size(), 1000000u);
  EXPECT_EQ(op_count_stack.top(), 999999);

  for (auto i = 0; i < 500000; ++i)
    op_count_stack.pop();
  EXPECT_EQ(op_count_stack.size(), 500000u);
  EXPECT_EQ(op_count_stack.top(), 499999);
  for (auto i = 0; i < 500000; ++i)
    op_count_stack.pop();
  EXPECT_TRUE(op_count_stack.empty());
}

TEST_F(linked_stack_fixture, copy_constructor) {
  for (operation_counter i = 0; i < 1000000; ++i)
    op_count_stack.push(i);

  EXPECT_EQ(op_count_stack.size(), 1000000u);
  EXPECT_EQ(op_count_stack.top(), 999999);

  ds::linked_stack <operation_counter> copy_stack = op_count_stack;
  EXPECT_EQ(copy_stack.size(), 1000000u);
  EXPECT_EQ(copy_stack.top(), 999999);
  EXPECT_EQ(op_count_stack.size(), 1000000u);
  EXPECT_EQ(op_count_stack.top(), 999999);
  for (auto i = 0; i < 500000; ++i)
    copy_stack.pop();
  EXPECT_EQ(copy_stack.size(), 500000u);
  EXPECT_EQ(copy_stack.top(), 499999);
  for (auto i = 0; i < 500000; ++i)
    copy_stack.pop();
  EXPECT_TRUE(copy_stack.empty());
  for (auto i = 0; i < 500000; ++i)
    op_count_stack.pop();
  EXPECT_EQ(op_count_stack.size(), 500000u);
  EXPECT_EQ(op_count_stack.top(), 499999);
  for (auto i = 0; i < 500000; ++i)
    op_count_stack.pop();
  EXPECT_TRUE(op_count_stack.empty());
}

TEST_F(linked_stack_fixture, move_constructor) {
  for (operation_counter i = 0; i < 1000000; ++i)
    op_count_stack.push(i);

  EXPECT_EQ(op_count_stack.size(), 1000000u);
  EXPECT_EQ(op_count_stack.top(), 999999);

  ds::linked_stack <operation_counter> move_stack = std::move(op_count_stack);
  EXPECT_EQ(op_count_stack.size(), 0u);
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_THROW(op_count_stack.top(), ds::stack_empty_error);
  EXPECT_EQ(move_stack.size(), 1000000u);
  EXPECT_EQ(move_stack.top(), 999999);
  for (auto i = 0; i < 500000; ++i)
    move_stack.pop();
  EXPECT_EQ(move_stack.size(), 500000u);
  EXPECT_EQ(move_stack.top(), 499999);
  for (auto i = 0; i < 500000; ++i)
    move_stack.pop();
  EXPECT_TRUE(move_stack.empty());
}

TEST_F(linked_stack_fixture, assign_operator) {
  for (operation_counter i = 0; i < 1000; ++i)
    op_count_stack.push(i);

  EXPECT_EQ(op_count_stack.size(), 1000u);
  EXPECT_EQ(op_count_stack.top(), 999);
  ds::linked_stack <operation_counter> other_stack;
  for (operation_counter i = 0; i < 10000; ++i)
    other_stack.push(i);

  EXPECT_EQ(other_stack.size(), 10000u);
  EXPECT_EQ(other_stack.top(), 9999);

  other_stack = op_count_stack;
  EXPECT_EQ(other_stack.size(), 1000u);
  EXPECT_EQ(other_stack.top(), 999);
}

TEST_F(linked_stack_fixture, move_assign_operator) {
  for (operation_counter i = 0; i < 1000; ++i)
    op_count_stack.push(i);

  EXPECT_EQ(op_count_stack.size(), 1000u);
  EXPECT_EQ(op_count_stack.top(), 999);
  ds::linked_stack <operation_counter> other_stack;
  other_stack = std::move(op_count_stack);

  EXPECT_EQ(other_stack.size(), 1000u);
  EXPECT_EQ(other_stack.top(), 999);
  EXPECT_EQ(op_count_stack.size(), 0u);
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_THROW(op_count_stack.top(), ds::stack_empty_error);
}

TEST_F(linked_stack_fixture, using_interface) {
  ds::stack <operation_counter>& stack = op_count_stack;

  for (operation_counter i = 0; i < 1000; ++i)
    stack.push(i);

  EXPECT_EQ(stack.size(), 1000u);
  EXPECT_EQ(stack.top(), 999);
  for (auto i = 0; i < 500; ++i)
    stack.pop();
  EXPECT_EQ(stack.size(), 500u);
  EXPECT_EQ(stack.top(), 499);
  for (auto i = 0; i < 500; ++i)
    stack.pop();
  EXPECT_TRUE(stack.empty());
}

TEST_F(linked_stack_fixture, equal) {
  ds::linked_stack <operation_counter> other_stack;
  ds::linked_stack <operation_counter> other_stack2;
  op_count_stack.push(1);
  op_count_stack.push(2);
  op_count_stack.push(3);
  op_count_stack.push(4);
  op_count_stack.push(5);
  // reflexive property of equality
  EXPECT_TRUE(op_count_stack == op_count_stack);
  EXPECT_FALSE(op_count_stack == other_stack);
  other_stack.push(1);
  other_stack.push(2);
  other_stack.push(3);
  other_stack.push(4);
  other_stack.push(6);
  EXPECT_FALSE(op_count_stack == other_stack);
  other_stack.pop();
  other_stack.push(5);
  //symmetric property of equality
  EXPECT_TRUE(op_count_stack == other_stack);
  EXPECT_TRUE(other_stack == op_count_stack);
  other_stack2 = other_stack;
  //transitive property of equality
  EXPECT_TRUE(op_count_stack == other_stack);
  EXPECT_TRUE(other_stack == other_stack2);
  EXPECT_TRUE(op_count_stack == other_stack2);
}

TEST_F(linked_stack_fixture, not_equal) {
  ds::linked_stack <operation_counter> other_stack;
  op_count_stack.push(1);
  op_count_stack.push(2);
  op_count_stack.push(3);
  op_count_stack.push(4);
  op_count_stack.push(5);
  EXPECT_TRUE(op_count_stack != other_stack);
  other_stack.push(1);
  other_stack.push(2);
  other_stack.push(3);
  other_stack.push(4);
  other_stack.push(6);
  EXPECT_TRUE(op_count_stack != other_stack);
  other_stack.pop();
  other_stack.push(5);
  EXPECT_FALSE(op_count_stack != other_stack);
}

TEST_F(linked_stack_fixture, less_than) {
  ds::linked_stack <operation_counter> other_stack;
  op_count_stack.push(1);
  op_count_stack.push(2);
  op_count_stack.push(3);
  op_count_stack.push(4);
  op_count_stack.push(5);
  EXPECT_FALSE(op_count_stack < other_stack);
  EXPECT_TRUE(other_stack < op_count_stack);
  other_stack.push(1);
  other_stack.push(2);
  other_stack.push(3);
  other_stack.push(4);
  other_stack.push(6);
  EXPECT_TRUE(op_count_stack < other_stack);
  EXPECT_FALSE(other_stack < op_count_stack);
  other_stack.pop();
  other_stack.push(5);
  EXPECT_FALSE(op_count_stack < other_stack);
  EXPECT_FALSE(other_stack < op_count_stack);
  other_stack.pop();
  EXPECT_FALSE(op_count_stack < other_stack);
  EXPECT_TRUE(other_stack < op_count_stack);
  op_count_stack.pop();
  op_count_stack.pop();
  EXPECT_TRUE(op_count_stack < other_stack);
  EXPECT_FALSE(other_stack < op_count_stack);
}

TEST_F(linked_stack_fixture, less_than_or_equal) {
  ds::linked_stack <operation_counter> other_stack;
  op_count_stack.push(1);
  op_count_stack.push(2);
  op_count_stack.push(3);
  op_count_stack.push(4);
  op_count_stack.push(5);
  EXPECT_FALSE(op_count_stack <= other_stack);
  EXPECT_TRUE(other_stack <= op_count_stack);
  other_stack.push(1);
  other_stack.push(2);
  other_stack.push(3);
  other_stack.push(4);
  other_stack.push(6);
  EXPECT_TRUE(op_count_stack <= other_stack);
  EXPECT_FALSE(other_stack <= op_count_stack);
  other_stack.pop();
  other_stack.push(5);
  EXPECT_TRUE(op_count_stack <= other_stack);
  EXPECT_TRUE(other_stack <= op_count_stack);
  other_stack.pop();
  EXPECT_FALSE(op_count_stack <= other_stack);
  EXPECT_TRUE(other_stack <= op_count_stack);
  op_count_stack.pop();
  op_count_stack.pop();
  EXPECT_TRUE(op_count_stack <= other_stack);
  EXPECT_FALSE(other_stack <= op_count_stack);
}

TEST_F(linked_stack_fixture, greater_than) {
  ds::linked_stack <operation_counter> other_stack;
  op_count_stack.push(1);
  op_count_stack.push(2);
  op_count_stack.push(3);
  op_count_stack.push(4);
  op_count_stack.push(5);
  EXPECT_TRUE(op_count_stack > other_stack);
  EXPECT_FALSE(other_stack > op_count_stack);
  other_stack.push(1);
  other_stack.push(2);
  other_stack.push(3);
  other_stack.push(4);
  other_stack.push(6);
  EXPECT_FALSE(op_count_stack > other_stack);
  EXPECT_TRUE(other_stack > op_count_stack);
  other_stack.pop();
  other_stack.push(5);
  EXPECT_FALSE(op_count_stack > other_stack);
  EXPECT_FALSE(other_stack > op_count_stack);
  other_stack.pop();
  EXPECT_TRUE(op_count_stack > other_stack);
  EXPECT_FALSE(other_stack > op_count_stack);
  op_count_stack.pop();
  op_count_stack.pop();
  EXPECT_FALSE(op_count_stack > other_stack);
  EXPECT_TRUE(other_stack > op_count_stack);
}

TEST_F(linked_stack_fixture, greater_than_or_equal) {
  ds::linked_stack <operation_counter> other_stack;
  op_count_stack.push(1);
  op_count_stack.push(2);
  op_count_stack.push(3);
  op_count_stack.push(4);
  op_count_stack.push(5);
  EXPECT_TRUE(op_count_stack >= other_stack);
  EXPECT_FALSE(other_stack >= op_count_stack);
  other_stack.push(1);
  other_stack.push(2);
  other_stack.push(3);
  other_stack.push(4);
  other_stack.push(6);
  EXPECT_FALSE(op_count_stack >= other_stack);
  EXPECT_TRUE(other_stack >= op_count_stack);
  other_stack.pop();
  other_stack.push(5);
  EXPECT_TRUE(op_count_stack >= other_stack);
  EXPECT_TRUE(other_stack >= op_count_stack);
  other_stack.pop();
  EXPECT_TRUE(op_count_stack >= other_stack);
  EXPECT_FALSE(other_stack >= op_count_stack);
  op_count_stack.pop();
  op_count_stack.pop();
  EXPECT_FALSE(op_count_stack >= other_stack);
  EXPECT_TRUE(other_stack >= op_count_stack);
}

TEST_F(linked_stack_fixture, clear) {
  op_count_stack.push(1);
  op_count_stack.push(2);
  op_count_stack.push(3);
  op_count_stack.push(4);
  op_count_stack.push(5);
  EXPECT_FALSE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 5u);
  EXPECT_EQ(op_count_stack.top(), 5);
  op_count_stack.clear();
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 0u);
  EXPECT_THROW(op_count_stack.pop(), ds::stack_empty_error);
  EXPECT_THROW(op_count_stack.top(), ds::stack_empty_error);
}

TEST_F(linked_stack_fixture, to_vector) {
  std::vector<operation_counter> val = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  for (operation_counter i = 0; i < 10; ++i)
    op_count_stack.push(i);
  EXPECT_EQ(op_count_stack.size(), 10u);
  EXPECT_EQ(op_count_stack.top(), 9);

  ASSERT_EQ(op_count_stack.to_vector(), val);
}