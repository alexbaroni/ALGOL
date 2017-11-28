/**
 * \file
 * Linked queue implementation.
 */

#ifndef ALGOL_DS_LINKED_QUEUE_HPP
#define ALGOL_DS_LINKED_QUEUE_HPP

#include <algorithm>
#include <memory>
#include <cassert>
#include "queue.hpp"
#include "stl2/concepts.hpp"

namespace algol::ds {
  namespace concepts = std::experimental::ranges;
  /**
   * \brief Implementation of the Queue ADT using a linked structure
   * \details see class [queue](@ref queue)
   * \tparam T type of the items stored in the queue
   * \invariant The item that is accessible at the front of the queue is the item that has
   * least recently been enqueued onto it and not yet dequeued (removed)
   */
  template <concepts::CopyConstructible T>
  class linked_queue final : public queue<T> {
  public:
    using value_type = typename queue<T>::value_type;
    using reference = typename queue<T>::reference;
    using const_reference = typename queue<T>::const_reference;
    using size_type = typename queue<T>::size_type;

    /**
     * \brief Default constructor
     * \precondition None
     * \postcondition The queue is empty
     * \complexity O(1)
     */
    linked_queue () noexcept(std::is_nothrow_constructible_v<size_type, int>)
        : queue<T>(), items_ {size_type{0}}
    {
      front_node_->prev_ = front_node_.get();
      front_node_->next_ = rear_node_.get();
      rear_node_->prev_ = front_node_.get();
      rear_node_->next_ = rear_node_.get();
    }

    /**
     * \brief Construct a queue with values provided
     * \details The values are enqueued onto the queue starting at begin of initializer list and stopping at the end
     * If the initializer_list contains {1, 2, 3, 4} the queue will contains [1, 2, 3, 4]
     * \precondition None
     * \postcondition The queue size is the same of the initializer_list and all the items contained in the
     * initializer_list are enqueued onto the queue
     * \complexity O(N)
     * \param values The items to be enqueued onto the queue
     */
    linked_queue (std::initializer_list<value_type> values) : linked_queue()
    {
      for (auto const& v : values)
        enqueue_(v);
    }

    /**
     * \brief Copy constructor
     * \precondition None
     * \postcondition This queue is equal to the provided queue
     * \complexity O(N)
     * \param rhs The queue to be copied
     */
    linked_queue (linked_queue const& rhs) : linked_queue()
    {
      linked_queue queue;

      if (!rhs.empty()) {
        for (auto i = size_type{0}; i < rhs.items_; ++i) {
          queue.enqueue_((node * ) ::operator new(sizeof(node)));
        }

        node* this_iter = queue.front_node_->next_;
        node* rhs_iter = rhs.front_node_->next_;

        while (rhs_iter != rhs.rear_node_.get()) {
          new(std::addressof(this_iter->value_)) T(rhs_iter->value_);
          this_iter = this_iter->next_;
          rhs_iter = rhs_iter->next_;
        }
      }
      swap(queue);
    }

    /**
     * \brief Move constructor
     * \precondition None
     * \postcondition This queue is equal to the provided queue that becomes empty
     * \complexity O(1)
     * \param rhs The queue to be moved, items contained are 'stolen' from this queue
     */
    linked_queue (linked_queue&& rhs) noexcept :
        front_node_ {std::move(rhs.front_node_)}, rear_node_ {std::move(rhs.rear_node_)}, items_ {rhs.items_}
    {
      rhs.front_node_.reset();
      rhs.rear_node_.reset();
      rhs.items_ = size_type{0};
    }

    /**
     * \brief Assignment operator
     * \details The actual items of the queue are destroyed and are replaced with the items of the provided queue
     * \precondition None
     * \postcondition This queue is equal to the provided queue
     * \complexity O(N)
     * \param rhs The queue to be copied
     * \return The queue containing the provided queue items
     */
    linked_queue& operator= (linked_queue const& rhs)
    {
      linked_queue temp {rhs};
      swap(temp);
      return *this;
    }

    /**
     * \brief Move assignment operator
     * \details The actual items of the queue are destroyed and are replaced with the items of the provided queue
     * \precondition None
     * \postcondition This queue is equal to the provided queue that becomes empty
     * \complexity O(1)
     * \param rhs The queue to be moved, items contained are 'stolen' from this queue
     * \return The queue containing the provided queue items
     */
    linked_queue& operator= (linked_queue&& rhs) noexcept
    {
      linked_queue temp {std::move(rhs)};
      swap(temp);
      return *this;
    }

    /**
     * \brief Destructor
     * \precondition None
     * \postcondition The queue items are destroyed
     * \complexity O(N)
     */
    ~linked_queue ()
    {
      while (!empty_()) {
        dequeue_();
      }
    }

    /**
     * \brief Equality operator
     * \details It must be reflexive, symmetric and transitive
     * \precondition None
     * \postcondition The queue is unchanged
     * \complexity O(N)
     * \param rhs The queue to be compared with this
     * \return True if the items are the same and in the same order, false otherwise
     */

    bool operator== (linked_queue const& rhs) const
    requires concepts::EqualityComparable<T>
    {
      if (items_ != rhs.items_)
        return false;

      node* this_iter = front_node_->next_;
      node* rhs_iter = rhs.front_node_->next_;

      while (this_iter != rear_node_.get() && rhs_iter != rhs.rear_node_.get()) {
        if (this_iter->value_ != rhs_iter->value_)
          return false;

        this_iter = this_iter->next_;
        rhs_iter = rhs_iter->next_;
      }

      return this_iter == rear_node_.get()  && rhs_iter == rhs.rear_node_.get();
    }

    /**
     * \brief Inequality operator
     * \details Implemented in terms of equality operator
     * \precondition None
     * \postcondition The queue is unchanged
     * \complexity O(N)
     * \param rhs The queue to be compared with this
     * \return True if the items are not the same or not in the same order, false otherwise
     */

    bool operator!= (linked_queue const& rhs) const
    requires concepts::EqualityComparable<T>
    {
      return !(*this == rhs);
    }

    /**
     * \brief Less than operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two queues are compared element by element
     * - The first mismatching item defines which queues is lexicographically less or greater than the other
     * - If one queue is a prefix of another, the shorter queue is lexicographically less than the other
     * - If two queues have equivalent elements and are of the same length, then the queues are lexicographically equal
     * - An empty queue is lexicographically less than any non-empty queue
     * - Two empty queues are lexicographically equal
     * \precondition None
     * \postcondition The queue is unchanged
     * \complexity O(N)
     * \param rhs The queue to be compared with this
     * \return True if this queue is lexicographically less than the provided queue, false otherwise
     */
    bool operator< (linked_queue const& rhs) const
    requires concepts::StrictTotallyOrdered<T>
    {
      node* this_iter = front_node_->next_;
      node* rhs_iter = rhs.front_node_->next_;

      while (this_iter != rear_node_.get() && rhs_iter != rhs.rear_node_.get()) {
        if (this_iter->value_ < rhs_iter->value_)
          return true;

        if (this_iter->value_ > rhs_iter->value_)
          return false;

        this_iter = this_iter->next_;
        rhs_iter = rhs_iter->next_;
      }

      return this_iter == rear_node_.get()  && rhs_iter != rhs.rear_node_.get();
    }

    /**
     * \brief Less than or equal operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two queues are compared element by element
     * - The first mismatching item defines which queues is lexicographically less or greater than the other
     * - If one queue is a prefix of another, the shorter queue is lexicographically less than the other
     * - If two queues have equivalent elements and are of the same length, then the queues are lexicographically equal
     * - An empty queue is lexicographically less than any non-empty queue
     * - Two empty queues are lexicographically equal
     * \precondition None
     * \postcondition The queue is unchanged
     * \complexity O(N)
     * \param rhs The queue to be compared with this
     * \return True if this queue is lexicographically less than or equal to the provided queue, false otherwise
     */
    bool operator<= (linked_queue const& rhs) const
    requires concepts::StrictTotallyOrdered<T>
    {
      return !(*this > rhs);
    }

    /**
     * \brief Greater than operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two queues are compared element by element
     * - The first mismatching item defines which queues is lexicographically less or greater than the other
     * - If one queue is a prefix of another, the shorter queue is lexicographically less than the other
     * - If two queues have equivalent elements and are of the same length, then the queues are lexicographically equal
     * - An empty queue is lexicographically less than any non-empty queue
     * - Two empty queues are lexicographically equal
     * \precondition None
     * \postcondition The queue is unchanged
     * \complexity O(N)
     * \param rhs The queue to be compared with this
     * \return True if this queue is lexicographically greater than the provided queue, false otherwise
     */
    bool operator> (linked_queue const& rhs) const
    requires concepts::StrictTotallyOrdered<T>
    {
      return rhs < *this;
    }

    /**
     * \brief Greater than or equal operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two queues are compared element by element
     * - The first mismatching item defines which queues is lexicographically less or greater than the other
     * - If one queue is a prefix of another, the shorter queue is lexicographically less than the other
     * - If two queues have equivalent elements and are of the same length, then the queues are lexicographically equal
     * - An empty queue is lexicographically less than any non-empty queue
     * - Two empty queues are lexicographically equal
     * \precondition None
     * \postcondition The queue is unchanged
     * \complexity O(N)
     * \param rhs The queue to be compared with this
     * \return True if this queue is lexicographically greater than or equal to the provided queue, false otherwise
     */
    bool operator>= (linked_queue const& rhs) const
    requires concepts::StrictTotallyOrdered<T>
    {
      return !(*this < rhs);
    }

    /**
     * \brief Swaps the items of this queue with the items of the provided queue
     * \details noexcept operation, it cannot throw
     * \precondition None
     * \postcondition This queue becomes the rhs queue and viceversa
     * \complexity O(1)
     * \param rhs The queue to be swapped with this
     */
    void swap (linked_queue& rhs) noexcept
    {
      using std::swap;
      swap(front_node_, rhs.front_node_);
      swap(rear_node_, rhs.rear_node_);
      swap(items_, rhs.items_);
    }

  private:
    struct node {
      value_type value_;
      node* next_;
      node* prev_;
    };

    bool empty_ () const final
    {
      return items_ == 0;
    }

    bool full_ () const final
    {
      return false;
    }

    size_type size_ () const final
    {
      return items_;
    }

    const_reference front_ () const& final
    {
      return front_node_->next_->value_;
    }

    void enqueue_ (value_type const& value) final
    {
      enqueue_(new node {value, nullptr, nullptr});
    }

    void enqueue_ (value_type&& value) final
    {
      enqueue_(new node {std::move(value), nullptr, nullptr});
    }

    void dequeue_ () final
    {
      node* node_to_dequeue = front_node_->next_;
      front_node_->next_ = front_node_->next_->next_;
      front_node_->next_->prev_ = front_node_.get();
      items_--;
      delete node_to_dequeue;
    }

    void clear_ () final
    {
      linked_queue temp {};
      swap(temp);
    }

    std::vector<value_type> to_vector_ () const final
    {
      std::vector<value_type> vector {};
      vector.reserve(size_());

      node* this_iter = front_node_->next_;

      while (this_iter != rear_node_.get()) {
        vector.emplace_back(this_iter->value_);
        this_iter = this_iter->next_;
      }
      return vector;
    }

    void enqueue_ (node* node_to_enqueue)
    {
      node_to_enqueue->next_ = rear_node_.get();
      node_to_enqueue->prev_ = rear_node_->prev_;
      rear_node_->prev_->next_ = node_to_enqueue;
      rear_node_->prev_ = node_to_enqueue;
      items_++;
    }

    std::unique_ptr<node> front_node_ = std::make_unique<node>();
    std::unique_ptr<node> rear_node_ = std::make_unique<node>();
    size_type items_;
  };

  /**
   * \brief Exchanges the items of lhs and rhs queues.
   * \details Non member function, noexcept it cannot fail.
   * \tparam T type of the items stored in the queue.
   * \precondition None.
   * \postcondition The lhs queue becomes the rhs queue and viceversa.
   * \complexity O(1)
   * \param lhs Stack to be exchanged with rhs.
   * \param rhs Stack to be exchanged with lhs.
   */
  template <typename T>
  void swap (linked_queue<T>& lhs, linked_queue<T>& rhs) noexcept
  {
    lhs.swap(rhs);
  }
}

#endif //ALGOL_DS_LINKED_QUEUE_HPP
