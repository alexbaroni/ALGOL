#include <vector>
#include <memory>

#include "algol/ds/stack/stack.hpp"
#include "algol/ds/stack/fixed_stack.hpp"
#include "algol/perf/operation_counter.hpp"
#include "gtest/gtest.h"

namespace ds = algol::ds;

using operation_counter = algol::perf::operation_counter<std::int32_t, std::uint64_t>;

class fixed_stack_fixture : public ::testing::Test {
protected:
  ds::fixed_stack<operation_counter, 100> op_count_stack;
};

TEST_F(fixed_stack_fixture, axioms)
{
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

TEST_F(fixed_stack_fixture, constructor)
{
  EXPECT_FALSE(!op_count_stack.empty());
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 0u);
  EXPECT_FALSE(op_count_stack.full());
  EXPECT_TRUE(!op_count_stack.full());
}

TEST_F(fixed_stack_fixture, initilizer_list)
{
  std::vector<operation_counter> val = {6, 5, 4, 3, 2, 1};
  ds::fixed_stack<operation_counter, 6> init_list_stack {1, 2, 3, 4, 5, 6};
  EXPECT_FALSE(init_list_stack.empty());
  EXPECT_EQ(init_list_stack.size(), 6u);
  ASSERT_EQ(init_list_stack.to_vector(), val);
}

TEST_F(fixed_stack_fixture, empty)
{
  auto const& stack = static_cast<const ds::fixed_stack<operation_counter, 100>&>(op_count_stack);
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 0u);
  EXPECT_THROW(op_count_stack.pop(), ds::stack_empty_error);
  EXPECT_THROW(op_count_stack.top(), ds::stack_empty_error);
  EXPECT_THROW(stack.top(), ds::stack_empty_error);
}

TEST_F(fixed_stack_fixture, one_element)
{
  op_count_stack.push(2);
  EXPECT_FALSE(op_count_stack.empty());
  EXPECT_EQ(op_count_stack.size(), 1u);
  EXPECT_EQ(op_count_stack.top(), 2);
  op_count_stack.emplace(6);
  EXPECT_EQ(op_count_stack.top(), 6);
  EXPECT_EQ(op_count_stack.size(), 2u);
}

TEST_F(fixed_stack_fixture, swap)
{
  ds::fixed_stack<operation_counter, 100> swap_stack;
  op_count_stack.push(2);
  op_count_stack.push(3);
  swap(swap_stack, op_count_stack);
  EXPECT_FALSE(swap_stack.empty());
  EXPECT_EQ(swap_stack.size(), 2u);
  EXPECT_EQ(swap_stack.top(), 3);
}

TEST_F(fixed_stack_fixture, five_elements)
{
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

TEST_F(fixed_stack_fixture, five_string_elements)
{
  ds::fixed_stack<std::string, 100> string_stack;
  string_stack.push("string 1");
  string_stack.push("string 2");
  string_stack.push("string 3");
  string_stack.push("string 4");
  string_stack.push("string 5");
  EXPECT_FALSE(string_stack.empty());
  EXPECT_EQ(string_stack.size(), 5u);
  EXPECT_EQ(string_stack.top(), "string 5");
  string_stack.pop();
  EXPECT_FALSE(string_stack.empty());
  EXPECT_EQ(string_stack.size(), 4u);
  EXPECT_EQ(string_stack.top(), "string 4");
  string_stack.pop();
  EXPECT_FALSE(string_stack.empty());
  EXPECT_EQ(string_stack.size(), 3u);
  EXPECT_EQ(string_stack.top(), "string 3");
  string_stack.pop();
  EXPECT_FALSE(string_stack.empty());
  EXPECT_EQ(string_stack.size(), 2u);
  EXPECT_EQ(string_stack.top(), "string 2");
  string_stack.pop();
  EXPECT_FALSE(string_stack.empty());
  EXPECT_EQ(string_stack.size(), 1u);
  EXPECT_EQ(string_stack.top(), "string 1");
  string_stack.pop();
  EXPECT_TRUE(string_stack.empty());
  EXPECT_EQ(string_stack.size(), 0u);
  EXPECT_THROW(string_stack.top(), ds::stack_empty_error);
}

TEST_F(fixed_stack_fixture, full_stack)
{
  for (int i = 0; i < 100; ++i)
    op_count_stack.push(i);
  EXPECT_TRUE(op_count_stack.full());
  EXPECT_THROW(op_count_stack.push(100), ds::stack_full_error);
}

TEST_F(fixed_stack_fixture, copy_constructor)
{
  for (operation_counter i = 0; i < 100; ++i)
    op_count_stack.push(i);

  EXPECT_EQ(op_count_stack.size(), 100u);
  EXPECT_EQ(op_count_stack.top(), 99);

  ds::fixed_stack<operation_counter, 100> copy_stack = op_count_stack;
  EXPECT_EQ(copy_stack.size(), 100u);
  EXPECT_EQ(copy_stack.top(), 99);
  EXPECT_EQ(op_count_stack.size(), 100u);
  EXPECT_EQ(op_count_stack.top(), 99);
  for (auto i = 0; i < 50; ++i)
    copy_stack.pop();
  EXPECT_EQ(copy_stack.size(), 50u);
  EXPECT_EQ(copy_stack.top(), 49);
  for (auto i = 0; i < 50; ++i)
    copy_stack.pop();
  EXPECT_TRUE(copy_stack.empty());
  for (auto i = 0; i < 50; ++i)
    op_count_stack.pop();
  EXPECT_EQ(op_count_stack.size(), 50u);
  EXPECT_EQ(op_count_stack.top(), 49);
  for (auto i = 0; i < 50; ++i)
    op_count_stack.pop();
  EXPECT_TRUE(op_count_stack.empty());
}

TEST_F(fixed_stack_fixture, move_constructor)
{
  for (operation_counter i = 0; i < 100; ++i)
    op_count_stack.push(i);

  EXPECT_EQ(op_count_stack.size(), 100u);
  EXPECT_EQ(op_count_stack.top(), 99);

  ds::fixed_stack<operation_counter, 100> move_stack = std::move(op_count_stack);
  EXPECT_EQ(op_count_stack.size(), 0u);
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_THROW(op_count_stack.top(), ds::stack_empty_error);
  EXPECT_EQ(move_stack.size(), 100u);
  EXPECT_EQ(move_stack.top(), 99);
  for (auto i = 0; i < 50; ++i)
    move_stack.pop();
  EXPECT_EQ(move_stack.size(), 50u);
  EXPECT_EQ(move_stack.top(), 49);
  for (auto i = 0; i < 50; ++i)
    move_stack.pop();
  EXPECT_TRUE(move_stack.empty());
}

TEST_F(fixed_stack_fixture, assign_operator)
{
  for (operation_counter i = 0; i < 100; ++i)
    op_count_stack.push(i);

  EXPECT_EQ(op_count_stack.size(), 100u);
  EXPECT_EQ(op_count_stack.top(), 99);
  ds::fixed_stack<operation_counter, 100> other_stack;
  for (operation_counter i = 0; i < 10; ++i)
    other_stack.push(i);

  EXPECT_EQ(other_stack.size(), 10u);
  EXPECT_EQ(other_stack.top(), 9);

  other_stack = op_count_stack;
  EXPECT_EQ(other_stack.size(), 100u);
  EXPECT_EQ(other_stack.top(), 99);
}

TEST_F(fixed_stack_fixture, move_assign_operator)
{
  for (operation_counter i = 0; i < 100; ++i)
    op_count_stack.push(i);

  EXPECT_EQ(op_count_stack.size(), 100u);
  EXPECT_EQ(op_count_stack.top(), 99);
  ds::fixed_stack<operation_counter, 100> other_stack;
  other_stack = std::move(op_count_stack);

  EXPECT_EQ(other_stack.size(), 100u);
  EXPECT_EQ(other_stack.top(), 99);
  EXPECT_EQ(op_count_stack.size(), 0u);
  EXPECT_TRUE(op_count_stack.empty());
  EXPECT_THROW(op_count_stack.top(), ds::stack_empty_error);
}

TEST_F(fixed_stack_fixture, using_interface)
{
  ds::stack <operation_counter>& stack = op_count_stack;

  for (operation_counter i = 0; i < 100; ++i)
    stack.push(i);

  EXPECT_EQ(stack.size(), 100u);
  EXPECT_EQ(stack.top(), 99);
  for (auto i = 0; i < 50; ++i)
    stack.pop();
  EXPECT_EQ(stack.size(), 50u);
  EXPECT_EQ(stack.top(), 49);
  for (auto i = 0; i < 50; ++i)
    stack.pop();
  EXPECT_TRUE(stack.empty());
}

TEST_F(fixed_stack_fixture, equal)
{
  ds::fixed_stack<operation_counter, 100> other_stack;
  ds::fixed_stack<operation_counter, 100> other_stack2;
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

TEST_F(fixed_stack_fixture, not_equal)
{
  ds::fixed_stack<operation_counter, 100> other_stack;
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

TEST_F(fixed_stack_fixture, less_than)
{
  ds::fixed_stack<operation_counter, 100> other_stack;
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

TEST_F(fixed_stack_fixture, less_than_or_equal)
{
  ds::fixed_stack<operation_counter, 100> other_stack;
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

TEST_F(fixed_stack_fixture, greater_than)
{
  ds::fixed_stack<operation_counter, 100> other_stack;
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

TEST_F(fixed_stack_fixture, greater_than_or_equal)
{
  ds::fixed_stack<operation_counter, 100> other_stack;
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

TEST_F(fixed_stack_fixture, clear)
{
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

TEST_F(fixed_stack_fixture, to_vector)
{
  std::vector<operation_counter> val = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  for (operation_counter i = 0; i < 10; ++i)
    op_count_stack.push(i);
  EXPECT_EQ(op_count_stack.size(), 10u);
  EXPECT_EQ(op_count_stack.top(), 9);

  ASSERT_EQ(op_count_stack.to_vector(), val);
}