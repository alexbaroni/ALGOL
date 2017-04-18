#include <vector>

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

TEST_F(linked_stack_fixture, constructor) {
  EXPECT_FALSE(!op_count_stack.empty());
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 0u);
}

TEST_F(linked_stack_fixture, empty) {
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 0u);
  EXPECT_THROW(op_count_stack.pop(), ds::stack_empty_error);
  EXPECT_THROW(op_count_stack.top(), ds::stack_empty_error);
  EXPECT_THROW({ static_cast<const ds::linked_stack <operation_counter> &>(op_count_stack).top(); },
               ds::stack_empty_error);
}

TEST_F(linked_stack_fixture, one_element) {
  op_count_stack.push(2);
  EXPECT_FALSE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 1u);
  EXPECT_EQ(op_count_stack.top(), 2);
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
  ds::stack <operation_counter> &stack = op_count_stack;

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

TEST_F(linked_stack_fixture, to_vector) {
  std::vector<operation_counter> val = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  for (operation_counter i = 0; i < 10; ++i)
    op_count_stack.push(i);
  EXPECT_EQ(op_count_stack.size(), 10u);
  EXPECT_EQ(op_count_stack.top(), 9);

  ASSERT_EQ(op_count_stack.to_vector(), val);
}