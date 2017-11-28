#include <vector>
#include <memory>

#include "algol/ds/queue/queue.hpp"
#include "algol/ds/queue/linked_queue.hpp"
#include "algol/perf/operation_counter.hpp"
#include "gtest/gtest.h"

namespace ds = algol::ds;

using operation_counter = algol::perf::operation_counter<std::int32_t, std::uint64_t>;

class linked_queue_fixture : public ::testing::Test {
protected:
  ds::linked_queue<operation_counter> op_count_queue;
};

TEST_F(linked_queue_fixture, axioms)
{
  // Note: Axioms for the ADT queue
  // new queue is empty and not full
  EXPECT_TRUE(op_count_queue.empty());
  EXPECT_FALSE(op_count_queue.full());
  // new queue is throws queue_empty_error on dequeue
  EXPECT_THROW(op_count_queue.dequeue(), ds::queue_empty_error);
  // new queue is throws queue_empty_error on front
  EXPECT_THROW(op_count_queue.front(), ds::queue_empty_error);
  op_count_queue.enqueue(1);
  // a queue with one item is not empty
  EXPECT_FALSE(op_count_queue.empty());
  // a queue with one item on front return that item
  EXPECT_EQ(op_count_queue.front(), 1);
  // a queue with one item does not throw on dequeue
  EXPECT_NO_THROW(op_count_queue.dequeue());
  op_count_queue.enqueue(1);
  auto size = op_count_queue.size();
  op_count_queue.enqueue(2);
  // a enqueue increase the size of the queue by 1
  EXPECT_EQ(op_count_queue.size(), size + 1u);
  size = op_count_queue.size();
  op_count_queue.dequeue();
  // a dequeue decrease the size of the queue by 1
  EXPECT_EQ(op_count_queue.size(), size - 1u);
}

TEST_F(linked_queue_fixture, constructor)
{
  EXPECT_FALSE(!op_count_queue.empty());
  EXPECT_TRUE(op_count_queue.empty());
  EXPECT_EQ(op_count_queue.size(), 0u);
  EXPECT_FALSE(op_count_queue.full());
  EXPECT_TRUE(!op_count_queue.full());
}

TEST_F(linked_queue_fixture, initilizer_list)
{
  std::vector<operation_counter> val = {1, 2, 3, 4, 5, 6};
  ds::linked_queue <operation_counter> init_list_queue {1, 2, 3, 4, 5, 6};
  EXPECT_FALSE(init_list_queue.empty());
  EXPECT_EQ(init_list_queue.size(), 6u);
  ASSERT_EQ(init_list_queue.to_vector(), val);
}

TEST_F(linked_queue_fixture, empty)
{
  EXPECT_TRUE(op_count_queue.empty());
  EXPECT_EQ(op_count_queue.size(), 0u);
  EXPECT_THROW(op_count_queue.dequeue(), ds::queue_empty_error);
  EXPECT_THROW(op_count_queue.front(), ds::queue_empty_error);
  EXPECT_THROW({ static_cast<const ds::linked_queue <operation_counter>&>(op_count_queue).front(); },
               ds::queue_empty_error);
}

TEST_F(linked_queue_fixture, one_element)
{
  op_count_queue.enqueue(2);
  EXPECT_FALSE(op_count_queue.empty());
  EXPECT_EQ(op_count_queue.size(), 1u);
  EXPECT_EQ(op_count_queue.front(), 2);
}

TEST_F(linked_queue_fixture, swap)
{
  ds::linked_queue <operation_counter> swap_queue;
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  swap(swap_queue, op_count_queue);
  EXPECT_FALSE(swap_queue.empty());
  EXPECT_EQ(swap_queue.size(), 2u);
  EXPECT_EQ(swap_queue.front(), 2);
}

TEST_F(linked_queue_fixture, five_elements)
{
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  op_count_queue.enqueue(4);
  op_count_queue.enqueue(5);
  EXPECT_FALSE(op_count_queue.empty());
  EXPECT_EQ(op_count_queue.size(), 5u);
  EXPECT_EQ(op_count_queue.front(), 1);
  op_count_queue.dequeue();
  EXPECT_FALSE(op_count_queue.empty());
  EXPECT_EQ(op_count_queue.size(), 4u);
  EXPECT_EQ(op_count_queue.front(), 2);
  op_count_queue.dequeue();
  EXPECT_FALSE(op_count_queue.empty());
  EXPECT_EQ(op_count_queue.size(), 3u);
  EXPECT_EQ(op_count_queue.front(), 3);
  op_count_queue.dequeue();
  EXPECT_FALSE(op_count_queue.empty());
  EXPECT_EQ(op_count_queue.size(), 2u);
  EXPECT_EQ(op_count_queue.front(), 4);
  op_count_queue.dequeue();
  EXPECT_FALSE(op_count_queue.empty());
  EXPECT_EQ(op_count_queue.size(), 1u);
  EXPECT_EQ(op_count_queue.front(), 5);
  op_count_queue.dequeue();
  EXPECT_TRUE(op_count_queue.empty());
  EXPECT_EQ(op_count_queue.size(), 0u);
  EXPECT_THROW(op_count_queue.front(), ds::queue_empty_error);
}

TEST_F(linked_queue_fixture, five_string_elements)
{
  ds::linked_queue<std::string> string_queue;

  string_queue.enqueue("string 1");
  string_queue.enqueue("string 2");
  string_queue.enqueue("string 3");
  string_queue.enqueue("string 4");
  string_queue.enqueue("string 5");
  EXPECT_FALSE(string_queue.empty());
  EXPECT_EQ(string_queue.size(), 5u);
  EXPECT_EQ(string_queue.front(), "string 1");
  string_queue.dequeue();
  EXPECT_FALSE(string_queue.empty());
  EXPECT_EQ(string_queue.size(), 4u);
  EXPECT_EQ(string_queue.front(), "string 2");
  string_queue.dequeue();
  EXPECT_FALSE(string_queue.empty());
  EXPECT_EQ(string_queue.size(), 3u);
  EXPECT_EQ(string_queue.front(), "string 3");
  string_queue.dequeue();
  EXPECT_FALSE(string_queue.empty());
  EXPECT_EQ(string_queue.size(), 2u);
  EXPECT_EQ(string_queue.front(), "string 4");
  string_queue.dequeue();
  EXPECT_FALSE(string_queue.empty());
  EXPECT_EQ(string_queue.size(), 1u);
  EXPECT_EQ(string_queue.front(), "string 5");
  string_queue.dequeue();
  EXPECT_TRUE(string_queue.empty());
  EXPECT_EQ(string_queue.size(), 0u);
  EXPECT_THROW(string_queue.front(), ds::queue_empty_error);
}

TEST_F(linked_queue_fixture, big_queue)
{
  for (operation_counter i = 0; i < 1000000; ++i)
    op_count_queue.enqueue(i);
  EXPECT_EQ(op_count_queue.size(), 1000000u);
  EXPECT_EQ(op_count_queue.front(), 0);

  for (auto i = 0; i < 500000; ++i)
    op_count_queue.dequeue();
  EXPECT_EQ(op_count_queue.size(), 500000u);
  EXPECT_EQ(op_count_queue.front(), 500000u);
  for (auto i = 0; i < 500000; ++i)
    op_count_queue.dequeue();
  EXPECT_TRUE(op_count_queue.empty());
}

TEST_F(linked_queue_fixture, copy_constructor)
{
  for (operation_counter i = 0; i < 1000000; ++i)
    op_count_queue.enqueue(i);

  EXPECT_EQ(op_count_queue.size(), 1000000u);
  EXPECT_EQ(op_count_queue.front(), 0);

  ds::linked_queue <operation_counter> copy_queue = op_count_queue;
  EXPECT_EQ(copy_queue.size(), 1000000u);
  EXPECT_EQ(copy_queue.front(), 0);
  EXPECT_EQ(op_count_queue.size(), 1000000u);
  EXPECT_EQ(op_count_queue.front(), 0);
  for (auto i = 0; i < 500000; ++i)
    copy_queue.dequeue();
  EXPECT_EQ(copy_queue.size(), 500000u);
  EXPECT_EQ(copy_queue.front(), 500000u);
  for (auto i = 0; i < 500000; ++i)
    copy_queue.dequeue();
  EXPECT_TRUE(copy_queue.empty());
  for (auto i = 0; i < 500000; ++i)
    op_count_queue.dequeue();
  EXPECT_EQ(op_count_queue.size(), 500000u);
  EXPECT_EQ(op_count_queue.front(), 500000);
  for (auto i = 0; i < 500000; ++i)
    op_count_queue.dequeue();
  EXPECT_TRUE(op_count_queue.empty());
}

TEST_F(linked_queue_fixture, move_constructor)
{
  for (operation_counter i = 0; i < 1000000; ++i)
    op_count_queue.enqueue(i);

  EXPECT_EQ(op_count_queue.size(), 1000000u);
  EXPECT_EQ(op_count_queue.front(), 0);

  ds::linked_queue <operation_counter> move_queue = std::move(op_count_queue);
  EXPECT_EQ(op_count_queue.size(), 0u);
  EXPECT_TRUE(op_count_queue.empty());
  EXPECT_THROW(op_count_queue.front(), ds::queue_empty_error);
  EXPECT_EQ(move_queue.size(), 1000000u);
  EXPECT_EQ(move_queue.front(), 0);
  for (auto i = 0; i < 500000; ++i)
    move_queue.dequeue();
  EXPECT_EQ(move_queue.size(), 500000u);
  EXPECT_EQ(move_queue.front(), 500000);
  for (auto i = 0; i < 500000; ++i)
    move_queue.dequeue();
  EXPECT_TRUE(move_queue.empty());
}

TEST_F(linked_queue_fixture, assign_operator)
{
  for (operation_counter i = 0; i < 1000; ++i)
    op_count_queue.enqueue(i);

  EXPECT_EQ(op_count_queue.size(), 1000u);
  EXPECT_EQ(op_count_queue.front(), 0);
  ds::linked_queue <operation_counter> other_queue;
  for (operation_counter i = 0; i < 10000; ++i)
    other_queue.enqueue(i);

  EXPECT_EQ(other_queue.size(), 10000u);
  EXPECT_EQ(other_queue.front(), 0);

  other_queue = op_count_queue;
  EXPECT_EQ(other_queue.size(), 1000u);
  EXPECT_EQ(other_queue.front(), 0);
}

TEST_F(linked_queue_fixture, move_assign_operator)
{
  for (operation_counter i = 0; i < 1000; ++i)
    op_count_queue.enqueue(i);

  EXPECT_EQ(op_count_queue.size(), 1000u);
  EXPECT_EQ(op_count_queue.front(), 0);
  ds::linked_queue <operation_counter> other_queue;
  other_queue = std::move(op_count_queue);

  EXPECT_EQ(other_queue.size(), 1000u);
  EXPECT_EQ(other_queue.front(), 0);
  EXPECT_EQ(op_count_queue.size(), 0u);
  EXPECT_TRUE(op_count_queue.empty());
  EXPECT_THROW(op_count_queue.front(), ds::queue_empty_error);
}

TEST_F(linked_queue_fixture, using_interface)
{
  ds::queue <operation_counter>& queue = op_count_queue;

  for (operation_counter i = 0; i < 1000; ++i)
    queue.enqueue(i);

  EXPECT_EQ(queue.size(), 1000u);
  EXPECT_EQ(queue.front(), 0);
  for (auto i = 0; i < 500; ++i)
    queue.dequeue();
  EXPECT_EQ(queue.size(), 500u);
  EXPECT_EQ(queue.front(), 500);
  for (auto i = 0; i < 500; ++i)
    queue.dequeue();
  EXPECT_TRUE(queue.empty());
}

TEST_F(linked_queue_fixture, equal)
{
  ds::linked_queue <operation_counter> other_queue;
  ds::linked_queue <operation_counter> other_queue2;
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  op_count_queue.enqueue(4);
  op_count_queue.enqueue(5);
  // reflexive property of equality
  EXPECT_TRUE(op_count_queue == op_count_queue);
  EXPECT_FALSE(op_count_queue == other_queue);
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(6);
  EXPECT_FALSE(op_count_queue == other_queue);
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(5);
  //symmetric property of equality
  EXPECT_TRUE(op_count_queue == other_queue);
  EXPECT_TRUE(other_queue == op_count_queue);
  other_queue2 = other_queue;
  //transitive property of equality
  EXPECT_TRUE(op_count_queue == other_queue);
  EXPECT_TRUE(other_queue == other_queue2);
  EXPECT_TRUE(op_count_queue == other_queue2);
}

TEST_F(linked_queue_fixture, not_equal)
{
  ds::linked_queue <operation_counter> other_queue;
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  op_count_queue.enqueue(4);
  op_count_queue.enqueue(5);
  EXPECT_TRUE(op_count_queue != other_queue);
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(6);
  EXPECT_TRUE(op_count_queue != other_queue);
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(5);
  EXPECT_FALSE(op_count_queue != other_queue);
}

TEST_F(linked_queue_fixture, less_than)
{
  ds::linked_queue <operation_counter> other_queue;
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  op_count_queue.enqueue(4);
  op_count_queue.enqueue(5);
  EXPECT_FALSE(op_count_queue < other_queue);
  EXPECT_TRUE(other_queue < op_count_queue);
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(6);
  EXPECT_TRUE(op_count_queue < other_queue);
  EXPECT_FALSE(other_queue < op_count_queue);
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(5);
  EXPECT_FALSE(op_count_queue < other_queue);
  EXPECT_FALSE(other_queue < op_count_queue);
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  EXPECT_FALSE(op_count_queue < other_queue);
  EXPECT_TRUE(other_queue < op_count_queue);
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  EXPECT_TRUE(op_count_queue < other_queue);
  EXPECT_FALSE(other_queue < op_count_queue);
}

TEST_F(linked_queue_fixture, less_than_or_equal)
{
  ds::linked_queue <operation_counter> other_queue;
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  op_count_queue.enqueue(4);
  op_count_queue.enqueue(5);
  EXPECT_FALSE(op_count_queue <= other_queue);
  EXPECT_TRUE(other_queue <= op_count_queue);
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(6);
  EXPECT_TRUE(op_count_queue <= other_queue);
  EXPECT_FALSE(other_queue <= op_count_queue);
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(5);
  EXPECT_TRUE(op_count_queue <= other_queue);
  EXPECT_TRUE(other_queue <= op_count_queue);
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  EXPECT_FALSE(op_count_queue <= other_queue);
  EXPECT_TRUE(other_queue <= op_count_queue);
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  EXPECT_TRUE(op_count_queue <= other_queue);
  EXPECT_FALSE(other_queue <= op_count_queue);
}

TEST_F(linked_queue_fixture, greater_than)
{
  ds::linked_queue <operation_counter> other_queue;
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  op_count_queue.enqueue(4);
  op_count_queue.enqueue(5);
  EXPECT_TRUE(op_count_queue > other_queue);
  EXPECT_FALSE(other_queue > op_count_queue);
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(6);
  EXPECT_FALSE(op_count_queue > other_queue);
  EXPECT_TRUE(other_queue > op_count_queue);
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(5);
  EXPECT_FALSE(op_count_queue > other_queue);
  EXPECT_FALSE(other_queue > op_count_queue);
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  EXPECT_TRUE(op_count_queue > other_queue);
  EXPECT_FALSE(other_queue > op_count_queue);
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  EXPECT_FALSE(op_count_queue > other_queue);
  EXPECT_TRUE(other_queue > op_count_queue);
}

TEST_F(linked_queue_fixture, greater_than_or_equal)
{
  ds::linked_queue <operation_counter> other_queue;
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  op_count_queue.enqueue(4);
  op_count_queue.enqueue(5);
  EXPECT_TRUE(op_count_queue >= other_queue);
  EXPECT_FALSE(other_queue >= op_count_queue);
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(6);
  EXPECT_FALSE(op_count_queue >= other_queue);
  EXPECT_TRUE(other_queue >= op_count_queue);
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  other_queue.enqueue(5);
  EXPECT_TRUE(op_count_queue >= other_queue);
  EXPECT_TRUE(other_queue >= op_count_queue);
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.dequeue();
  other_queue.enqueue(1);
  other_queue.enqueue(2);
  other_queue.enqueue(3);
  other_queue.enqueue(4);
  EXPECT_TRUE(op_count_queue >= other_queue);
  EXPECT_FALSE(other_queue >= op_count_queue);
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.dequeue();
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  EXPECT_FALSE(op_count_queue >= other_queue);
  EXPECT_TRUE(other_queue >= op_count_queue);
}

TEST_F(linked_queue_fixture, clear)
{
  op_count_queue.enqueue(1);
  op_count_queue.enqueue(2);
  op_count_queue.enqueue(3);
  op_count_queue.enqueue(4);
  op_count_queue.enqueue(5);
  EXPECT_FALSE(op_count_queue.empty());
  EXPECT_EQ(op_count_queue.size(), 5u);
  EXPECT_EQ(op_count_queue.front(), 1);
  op_count_queue.clear();
  EXPECT_TRUE(op_count_queue.empty());
  EXPECT_EQ(op_count_queue.size(), 0u);
  EXPECT_THROW(op_count_queue.dequeue(), ds::queue_empty_error);
  EXPECT_THROW(op_count_queue.front(), ds::queue_empty_error);
}

TEST_F(linked_queue_fixture, to_vector)
{
  std::vector<operation_counter> val = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (operation_counter i = 0; i < 10; ++i)
    op_count_queue.enqueue(i);
  EXPECT_EQ(op_count_queue.size(), 10u);
  EXPECT_EQ(op_count_queue.front(), 0);

  ASSERT_EQ(op_count_queue.to_vector(), val);
}
