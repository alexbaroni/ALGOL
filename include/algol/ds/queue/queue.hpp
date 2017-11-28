/**
 * \file
 * Stack ADT
 */

#ifndef ALGOL_DS_QUEUE_HPP
#define ALGOL_DS_QUEUE_HPP

#include <vector>
#include <stdexcept>

namespace algol::ds {
  /**
   * \brief Base queue exception.
   * \details Can be used to catch every queue exceptions.
   */
  struct queue_error : public virtual std::logic_error {
#if defined(__clang__)
    using std::logic_error::logic_error;
#else

    explicit queue_error (std::string const& what_arg) : std::logic_error {what_arg}
    {}

#endif
  };

  /**
   * \brief Throwed when the queue is empty.
   * \details Throwed from front and dequeue operation.
   */
  struct queue_empty_error : public queue_error {
    explicit queue_empty_error (std::string const& what_arg) : std::logic_error {what_arg},
                                                               queue_error {what_arg}
    {}
  };

  /**
   * \brief Throwed when the queue is full.
   * \details Throwed from enqueue operation.
   */
  struct queue_full_error : public queue_error {
    explicit queue_full_error (std::string const& what_arg) : std::logic_error {what_arg},
                                                              queue_error {what_arg}
    {}
  };

  /**
   * \brief Queue ADT interface
   * \details A queue is a sequence that can be accessed in <b>'first-in, first-out' (FIFO) order</b>
   * The only accessible item is the one that was least recently added (pushed).
   * The preconditions of the operations are enforced, postconditions and invariant aren't enforced.
   * \tparam T type of the items stored in the queue.
   * \invariant The item that is accessible at the front of the queue is the item that has
   * least recently been enqueued onto it and not yet dequeued (removed).
   */
  template <typename T>
  class queue {
  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;
    using size_type = std::size_t;

    /**
     * \brief The queue is empty?
     * \precondition None
     * \postcondition Queue is not changed
     * \complexity O(1)
     * \return True if the queue is empty, false otherwise
     */
    bool empty () const
    {
      return empty_();
    };

    /**
     * \brief The queue is full?
     * \precondition None
     * \postcondition Queue is not changed
     * \complexity O(1)
     * \return True if the queue is full, false otherwise
     */
    bool full () const
    {
      return full_();
    };

    /**
     * \brief The size of the queue
     * \precondition None
     * \postcondition Queue is not changed
     * \complexity O(1)
     * \return The current number of the items on the queue
     */
    size_type size () const
    {
      return size_();
    }

    /**
     * \brief A constant reference at the item on the top of the queue
     * \precondition The queue is not empty
     * \postcondition Queue is not changed
     * \complexity O(1)
     * \throws queue_empty_error if the queue is empty
     * \return The item on the front of the queue
     */
    const_reference front () const&
    {
      if (empty_())
        throw queue_empty_error{"Attempting front() on empty queue"};

      return front_();
    }

    /**
     * \brief Enqueue the item passed onto the queue
     * \precondition The queue is not full
     * \postcondition The size of the Queue is increased by 1 and the item passed becomes the current rear
     * \complexity O(1)
     * \throws queue_full_error if the queue is full and the queue is not changed
     * \param value The item to enqueue onto the queue
     */
    void enqueue (value_type const& value)
    {
      if (full_())
        throw queue_full_error{"Attempting enqueue() on full queue"};

      enqueue_(value);
    }

    /**
     * \brief Enqueue the item passed onto the queue
     * \precondition The queue is not full
     * \postcondition The size of the Queue is increased by 1 and the item passed becomes the current rear
     * \complexity O(1)
     * \throws queue_full_error if the queue is full and the queue is not changed
     * \param value The item to enqueue onto the queue with move operation
     */
    void enqueue (value_type&& value)
    {
      if (full_())
        throw queue_full_error{"Attempting enqueue() on full queue"};

      enqueue_(std::forward<value_type>(value));
    }

    /**
     * \brief Dequeue the current front item from the queue
     * \precondition The queue is not empty
     * \postcondition The size of the Queue is decreased by 1 and the current front item is removed from the queue
     * \complexity O(1)
     * \throws queue_empty_error if the queue is empty
     */
    void dequeue ()
    {
      if (empty_())
        throw queue_empty_error{"Attempting dequeue() on empty queue"};

      dequeue_();
    }

    /**
     * \brief Clear the queue removing all the items
     * \details Invalidates any references or pointers referring to contained elements
     * \precondition None
     * \postcondition The queue is empty, the size becomes 0
     * \complexity O(1) or O(N) depends on the implementation
     */
    void clear ()
    {
      clear_();
    }

    /**
     * \brief Creates a vector with the items enqueued onto the queue
     * \precondition None
     * \postcondition The queue is unchanged
     * \complexity O(N)
     * \return A vector with the items enqueued onto the queue
     */
    std::vector<T> to_vector () const
    {
      return to_vector_();
    };

    queue () = default;
    queue (queue const&) = default;
    queue (queue&&) = default;
    queue& operator= (queue const&) = default;
    queue& operator= (queue&&) = default;
    virtual ~queue () = default;

  private:
    virtual bool empty_ () const = 0;
    virtual bool full_ () const = 0;
    virtual size_type size_ () const = 0;
    virtual const_reference front_ () const& = 0;
    virtual void enqueue_ (value_type const& value) = 0;
    virtual void enqueue_ (value_type&& value) = 0;
    virtual void dequeue_ () = 0;
    virtual void clear_ () = 0;
    virtual std::vector<T> to_vector_ () const = 0;
  };
}
#endif //ALGOL_DS_QUEUE_HPP
