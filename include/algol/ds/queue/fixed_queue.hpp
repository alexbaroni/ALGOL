/**
 * \file
 * Fixed queue implementation.
 */

#ifndef ALGOL_DS_FIXED_QUEUE_HPP
#define ALGOL_DS_FIXED_QUEUE_HPP

#include <algorithm>
#include <memory>
#include <cassert>
#include "queue.hpp"
#include "stl2/concepts.hpp"

namespace algol::ds {
  namespace concepts = std::experimental::ranges;

  /**
   * \brief Implementation of the Queue ADT using a fixed array
   * \details see class [queue](@ref queue)
   * \tparam T type of the items stored in the queue
   * \invariant The item that is accessible at the front of the queue is the item that has
   * least recently been enqueued onto it and not yet dequeued (removed)
   */
  template <concepts::CopyConstructible T, typename queue<T>::size_type N>
  class fixed_queue final : public queue<T> {
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
    fixed_queue ()
        : queue<T>(), items_ {size_type{0}}, front_item_ {size_type{0}}, rear_item_ {size_type{0}},
          array_ {std::make_unique<value_type[]>(N)}
    {}

    /**
     * \brief Construct a queue with values provided
     * \details The values are enqueued onto the queue starting at begin of initializer list and stopping at the end
     * If the initializer_list contains {1, 2, 3, 4} the stack will contains [1, 2, 3, 4]
     * \precondition None
     * \postcondition The queue size is the same of the initializer_list and all the items contained in the
     * initializer_list are enqueued onto the queue
     * \complexity O(N)
     * \param values The items to be enqueued onto the queue
     */
    fixed_queue (std::initializer_list<value_type> values) : fixed_queue()
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
    fixed_queue (fixed_queue const& rhs) : fixed_queue()
    {
      assert(rhs.items_ >= size_type{0} && rhs.items_ <= N);
      assert(rhs.front_item_ >= size_type{0} && rhs.front_item_ < N);
      assert(rhs.rear_item_ >= size_type{0} && rhs.rear_item_ < N);

      fixed_queue queue;

      if (!rhs.empty()) {
        for (auto i = size_type{0}; i < rhs.items_; ++i) {
          auto j = (rhs.front_item_ + i) % N;
          alloc_traits::destroy(allocator_, std::addressof(queue.array_[j]));
          alloc_traits::construct(allocator_, std::addressof(queue.array_[j]), value_type{rhs.array_[j]});
        }

        queue.items_ = rhs.items_;
        queue.front_item_ = rhs.front_item_;
        queue.rear_item_ = rhs.rear_item_;
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
    fixed_queue (fixed_queue&& rhs) noexcept
    : items_ {rhs.items_}, front_item_ {rhs.front_item_}, rear_item_ {rhs.rear_item_}, array_ {std::move(rhs.array_)}
    {
      assert(rhs.items_ >= size_type{0} && rhs.items_ <= N);
      assert(rhs.front_item_ >= size_type{0} && rhs.front_item_ < N);
      assert(rhs.rear_item_ >= size_type{0} && rhs.rear_item_ < N);

      rhs.items_ = size_type{0};
      rhs.front_item_ = size_type{0};
      rhs.rear_item_ = size_type{0};
      rhs.array_ = nullptr;
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
    fixed_queue& operator= (fixed_queue const& rhs)
    {
      assert(rhs.items_ >= size_type{0} && rhs.items_ <= N);
      assert(rhs.front_item_ >= size_type{0} && rhs.front_item_ < N);
      assert(rhs.rear_item_ >= size_type{0} && rhs.rear_item_ < N);

      fixed_queue temp {rhs};
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
    fixed_queue& operator= (fixed_queue&& rhs) noexcept
    {
      assert(rhs.items_ >= size_type{0} && rhs.items_ <= N);
      assert(rhs.front_item_ >= size_type{0} && rhs.front_item_ < N);
      assert(rhs.rear_item_ >= size_type{0} && rhs.rear_item_ < N);

      fixed_queue temp {std::move(rhs)};
      swap(temp);
      return *this;
    }

    /**
     * \brief Destructor
     * \precondition None
     * \postcondition The queue items are destroyed
     * \complexity O(N) Destructor calls
     */
    ~fixed_queue () = default;

    /**
     * \brief Emplace the item passed onto the queue
     * \precondition The queue is not full
     * \postcondition The size of the queue is increased by 1 and the item passed becomes the current rear
     * \complexity O(1)
     * \throws queue_full_error if the queue is full and the queue is not changed
     * \tparam Args parameters types for constructor of T
     * \param args parameters for constructor of T
     */
    template <typename... Args>
    std::enable_if_t<std::is_constructible_v<T, Args&& ...>, void>
    emplace (Args&& ... args)
    {
      emplace_(std::forward<Args>(args)...);
    }

    /**
     * \brief Emplace the item passed onto the queue
     * \precondition The queue is not full
     * \postcondition The size of the queue is increased by 1 and the item passed becomes the current rear
     * \complexity O(1)
     * \throws queue_full_error if the queue is full and the queue is not changed
     * \tparam U initializer list type for constructor of T
     * \tparam Args parameters types for constructor of T
     * \param ilist parameters for constructor of T
     * \param args initializer list for constructor of T
     */
    template <typename U, typename... Args>
    std::enable_if_t<std::is_constructible_v<T, std::initializer_list<U>, Args&& ...>, void>
    emplace (std::initializer_list<U> ilist, Args&& ... args)
    {
      emplace_(ilist, std::forward<Args>(args)...);
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

    bool operator== (fixed_queue const& rhs) const
    requires concepts::EqualityComparable<T>
    {
      assert(items_ >= size_type{0} && items_ <= N);
      assert(front_item_ >= size_type{0} && front_item_ < N);
      assert(rhs.items_ >= size_type{0} && rhs.items_ <= N);
      assert(rhs.front_item_ >= size_type{0} && rhs.front_item_ < N);

      if (items_ != rhs.items_)
        return false;

      for (auto i = size_type{ 0 }; i < items_; ++i) {
        auto j = (front_item_ + i) % N;
        auto k = (rhs.front_item_ + i) % N;
        if (array_[j] != rhs.array_[k])
          return false;
      }

      return true;
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

    bool operator!= (fixed_queue const& rhs) const
    requires concepts::EqualityComparable<T>
    {
      return !(*this == rhs);
    }

    /**
     * \brief Less than operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two queues are compared element by element
     * - The first mismatching item defines which queue is lexicographically less or greater than the other
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
    bool operator< (fixed_queue const& rhs) const
    requires concepts::StrictTotallyOrdered<T>
    {
      assert(items_ >= size_type{0} && items_ <= N);
      assert(front_item_ >= size_type{0} && front_item_ < N);
      assert(rhs.items_ >= size_type{0} && rhs.items_ <= N);
      assert(rhs.front_item_ >= size_type{0} && rhs.front_item_ < N);

      auto items = std::min(items_, rhs.items_);
      for (auto i = size_type{ 0 }; i < items; ++i) {
        auto j = (front_item_ + i) % N;
        auto k = (rhs.front_item_ + i) % N;
        if (array_[j] < rhs.array_[k])
          return true;

        if (array_[j] > rhs.array_[k])
          return false;
      }

      return items_ < rhs.items_;
    }

    /**
     * \brief Less than or equal operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two queues are compared element by element
     * - The first mismatching item defines which queue is lexicographically less or greater than the other
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
    bool operator<= (fixed_queue const& rhs) const
    requires concepts::StrictTotallyOrdered<T>
    {
      return !(*this > rhs);
    }

    /**
     * \brief Greater than operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two queues are compared element by element
     * - The first mismatching item defines which queue is lexicographically less or greater than the other
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
    bool operator> (fixed_queue const& rhs) const
    requires concepts::StrictTotallyOrdered<T>
    {
      return rhs < *this;
    }

    /**
     * \brief Greater than or equal operator
     * \details Lexicographical comparison is a operation with the following properties:
     * - Two queues are compared element by element
     * - The first mismatching item defines which queue is lexicographically less or greater than the other
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
    bool operator>= (fixed_queue const& rhs) const
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
    void swap (fixed_queue& rhs) noexcept
    {
      assert(items_ >= size_type{0} && items_ <= N);
      assert(front_item_ >= size_type{0} && front_item_ < N);
      assert(rear_item_ >= size_type{0} && rear_item_ < N);
      assert(rhs.items_ >= size_type{0} && rhs.items_ <= N);
      assert(rhs.front_item_ >= size_type{0} && rhs.front_item_ < N);
      assert(rhs.rear_item_ >= size_type{0} && rhs.rear_item_ < N);

      using std::swap;
      swap(items_, rhs.items_);
      swap(front_item_, rhs.front_item_);
      swap(rear_item_, rhs.rear_item_);
      swap(array_, rhs.array_);
    }

  private:
    bool empty_ () const final
    {
      assert(items_ >= size_type{0} && items_ <= N);

      return items_ == size_type{0};
    }

    bool full_ () const final
    {
      assert(items_ >= size_type{0} && items_ <= N);

      return items_ == N;
    }

    size_type size_ () const final
    {
      assert(items_ >= size_type{0} && items_ <= N);

      return items_;
    }

    const_reference front_ () const& final
    {
      assert(items_ >= size_type{0} && items_ <= N);
      assert(front_item_ >= size_type{0} && front_item_ < N);

      return array_[front_item_];
    }

    void enqueue_ (value_type const& value) final
    {
      assert(items_ >= size_type{0} && items_ < N);
      assert(rear_item_ >= size_type{0} && rear_item_ < N);

      alloc_traits::destroy(allocator_, std::addressof(array_[rear_item_]));
      alloc_traits::construct(allocator_, std::addressof(array_[rear_item_]), value_type{value});
      rear_item_++;
      rear_item_ %= N;
      items_++;
    }

    void enqueue_ (value_type&& value) final
    {
      assert(items_ >= size_type{0} && items_ < N);
      assert(rear_item_ >= size_type{0} && rear_item_ < N);

      alloc_traits::destroy(allocator_, std::addressof(array_[rear_item_]));
      alloc_traits::construct(allocator_, std::addressof(array_[rear_item_]), value_type{std::move(value)});
      rear_item_++;
      rear_item_ %= N;
      items_++;
    }

    void dequeue_ () final
    {
      assert(items_ > size_type{0} && items_ <= N);
      assert(front_item_ >= size_type{0} && front_item_ < N);

      front_item_++;
      front_item_ %= N;
      items_--;
    }


    void clear_ () final
    {
      assert(items_ >= size_type{0} && items_ <= N);
      assert(front_item_ >= size_type{0} && front_item_ < N);

      items_ = size_type{0};
      front_item_ = size_type{0};
      rear_item_ = size_type{0};
    }

    std::vector<value_type> to_vector_ () const final
    {
      assert(items_ >= size_type{0} && items_ <= N);
      assert(front_item_ >= size_type{0} && front_item_ < N);

      std::vector<value_type> vector {};
      vector.reserve(size_());

      for (auto i = size_type{0}; i < items_; ++i) {
        auto j = (front_item_ + i) % N;
        vector.emplace_back(array_[j]);
      }
      return vector;
    }

    template <typename... Args>
    void emplace_ (Args&& ... args) noexcept(std::is_nothrow_constructible<T, Args...>())
    {
      assert(items_ >= size_type{0} && items_ < N);
      assert(rear_item_ >= size_type{0} && rear_item_ < N);

      alloc_traits::destroy(allocator_, std::addressof(array_[rear_item_]));
      alloc_traits::construct(allocator_, std::addressof(array_[rear_item_]), value_type{std::forward<Args>(args)...});
      rear_item_++;
      rear_item_ %= N;
      items_++;
    }

    using alloc = std::allocator<value_type>;
    using alloc_traits = std::allocator_traits<alloc>;

    size_type items_;
    size_type front_item_;
    size_type rear_item_;
    std::unique_ptr<value_type[]> array_;
    alloc allocator_;
  };

  /**
   * \brief Exchanges the items of lhs and rhs queues
   * \details Non member function, noexcept it cannot fail
   * \tparam T type of the items stored in the queue
   * \precondition None
   * \postcondition The lhs queue becomes the rhs queue and viceversa
   * \complexity O(1)
   * \param lhs Queue to be exchanged with rhs
   * \param rhs Queue to be exchanged with lhs
   */
  template <typename T, typename queue<T>::size_type N>
  void swap (fixed_queue<T, N>& lhs, fixed_queue<T, N>& rhs) noexcept
  {
    lhs.swap(rhs);
  }
}

#endif //ALGOL_DS_FIXED_QUEUE_HPP
