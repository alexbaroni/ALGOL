#ifndef ALGOL_RESULT_RESULT_HPP
#define ALGOL_RESULT_RESULT_HPP

#include <algorithm>
#include <exception>
#include <utility>
#include <system_error>

namespace algol {
  template <typename T>
  class result {
  public:
    using value_type = T;

    ~result ()
    {
      if (has_value_)
        value_.~T();
      else if (has_error_)
        error_.~error_code();
      else
        exception_.~exception_ptr();
    }

    explicit result (T const& rhs) : value_(rhs), has_value_(true)
    {}

    explicit result (T&& rhs) : value_(std::move(rhs)), has_value_(true)
    {}

    template <typename... Args>
    explicit result (std::in_place_t, Args&& ... args) : value_(std::forward<Args>(args)...), has_value_(true)
    {}

    template <typename U, typename... Args>
    explicit result (std::in_place_t, std::initializer_list<U> ilist, Args&& ... args) :
        value_(ilist, std::forward<Args>(args)...), has_value_(true)
    {}

    explicit result (std::error_code const& rhs) : error_(rhs), has_error_(true)
    {}

    explicit result (std::error_code&& rhs) : error_(std::move(rhs)), has_error_(true)
    {}

    explicit result (std::exception_ptr const& rhs) : exception_(rhs), has_exception_(true)
    {}

    explicit result (std::exception_ptr&& rhs) : exception_(std::move(rhs)), has_exception_(true)
    {}

    result (result const& rhs) :
        has_value_(rhs.has_value_), has_error_(rhs.has_error_), has_exception_(rhs.has_exception_)
    {
      if (has_value_)
        new(&value_) T(rhs.value_);
      else if (has_error_)
        new(&error_) std::error_code(rhs.error_);
      else
        new(&exception_) std::exception_ptr(rhs.exception_);
    }

    result (result&& rhs) :
        has_value_(rhs.has_value_), has_error_(rhs.has_error_), has_exception_(rhs.has_exception_)
    {
      if (has_value_)
        new(&value_) T(std::move(rhs.value_));
      else if (has_error_)
        new(&error_) std::error_code(std::move(rhs.error_));
      else
        new(&exception_) std::exception_ptr(std::move(rhs.exception_));
    }

    operator T const& () const
    {
      if (has_value_)
        return value_;
      else if (has_error_)
        throw std::system_error(error_);
      else
        std::rethrow_exception(exception_);
    }

//    const T* operator-> () const;
//    const T& operator* () const& ;
//    const T&& operator* () const&& ;


    void swap (result& rhs) noexcept(std::is_nothrow_move_constructible<T>::value)
    {
      if (has_value_ && rhs.has_value_) {
        using std::swap;
        swap(value_, rhs.value_);
      }
      else if (has_error_ && rhs.has_error_) {
        std::swap(error_, rhs.error_);
      }
      else if (has_exception_ && rhs.has_exception_) {
        exception_.swap(rhs.exception_);
      }
      else if (has_value_ && rhs.has_error_) {
        auto t = std::move(rhs.error_);
        new(&rhs.value_) T(std::move(value_));
        new(&error_) std::error_code(t);
        std::swap(has_value_, rhs.has_value_);
        std::swap(has_error_, rhs.has_error_);
      }
      else if (has_value_ && rhs.has_exception_) {
        auto t = std::move(rhs.exception_);
        new(&rhs.value_) T(std::move(value_));
        new(&exception_) std::exception_ptr(t);
        std::swap(has_value_, rhs.has_value_);
        std::swap(has_exception_, rhs.has_exception_);
      }
      else if (has_error_ && rhs.has_exception_) {
        auto t = std::move(rhs.exception_);
        new(&rhs.error_) std::error_code(std::move(error_));
        new(&exception_) std::exception_ptr(t);
        std::swap(has_error_, rhs.has_error_);
        std::swap(has_exception_, rhs.has_exception_);
      }
      else if (has_error_ && rhs.has_value_) {
        rhs.swap(*this);
      }
      else if (has_exception_ && rhs.has_value_) {
        rhs.swap(*this);
      }
      else if (has_exception_ && rhs.has_error_) {
        rhs.swap(*this);
      }
    }

    explicit operator bool () const noexcept
    {
      return has_value_;
    }

    bool has_value ()
    { return has_value_; }

    bool has_error ()
    { return has_error_; }

    bool has_exception ()
    { return has_exception_; }

    template <std::size_t N>
    decltype(auto) get () const
    {
      if constexpr (N == 0)
      return (value_); //parens needed to get reference
    }

  private:
    union {
      T value_;
      std::error_code error_;
      std::exception_ptr exception_;
    };

    bool has_value_ = false;
    bool has_error_ = false;
    bool has_exception_ = false;

    result ()
    {}
  };

  template <>
  class result<void> {
  public:
    using value_type = void;

    ~result ()
    {
      if (has_error_)
        error_.~error_code();
      else if (has_exception_)
        exception_.~exception_ptr();
    }

    explicit result (std::error_code const& rhs) : error_(rhs), has_error_(true)
    {}

    explicit result (std::error_code&& rhs) : error_(std::move(rhs)), has_error_(true)
    {}

    explicit result (std::exception_ptr const& rhs) : exception_(rhs), has_exception_(true)
    {}

    explicit result (std::exception_ptr&& rhs) : exception_(std::move(rhs)), has_exception_(true)
    {}

    result (result const& rhs) :
        has_error_(rhs.has_error_), has_exception_(rhs.has_exception_)
    {
      if (has_error_)
        new(&error_) std::error_code(rhs.error_);
      else if (has_exception_)
        new(&exception_) std::exception_ptr(rhs.exception_);
    }

    result (result&& rhs) :
        has_error_(rhs.has_error_), has_exception_(rhs.has_exception_)
    {
      if (has_error_)
        new(&error_) std::error_code(std::move(rhs.error_));
      else if (has_exception_)
        new(&exception_) std::exception_ptr(std::move(rhs.exception_));
    }

    void swap (result& rhs)
    {
      if (has_error_ && rhs.has_error_) {
        std::swap(error_, rhs.error_);
      }
      else if (has_exception_ && rhs.has_exception_) {
        exception_.swap(rhs.exception_);
      }
      else if (has_error_ && rhs.has_exception_) {
        auto t = std::move(rhs.exception_);
        new(&rhs.error_) std::error_code(std::move(error_));
        new(&exception_) std::exception_ptr(t);
        std::swap(has_error_, rhs.has_error_);
        std::swap(has_exception_, rhs.has_exception_);
      }
      else if (has_exception_ && rhs.has_error_) {
        rhs.swap(*this);
      }
    }

    explicit operator bool () const noexcept
    {
      return false;
    }

    bool has_value ()
    { return false; }

    bool has_error ()
    { return has_error_; }

    bool has_exception ()
    { return has_exception_; }

  private:
    union {
      std::error_code error_;
      std::exception_ptr exception_;
    };

    bool has_error_ = false;
    bool has_exception_ = false;

    result ()
    {}
  };

// relational operator

  template <typename T>
  bool operator== (result<T> const& x, result<T> const& y)
  {
    return bool(x) != bool(y) ? false : bool(x) == false ? true : static_cast<T>(x) == static_cast<T>(y);
  }

  template <typename T>
  bool operator!= (result<T> const& x, result<T> const& y)
  {
    return !(x == y);
  }

  template <typename T>
  bool operator< (result<T> const& x, result<T> const& y)
  {
    return (!y) ? false : (!x) ? true : static_cast<T>(x) < static_cast<T>(y);
  }

  template <typename T>
  bool operator> (result<T> const& x, result<T> const& y)
  {
    return (y < x);
  }

  template <typename T>
  bool operator<= (result<T> const& x, result<T> const& y)
  {
    return !(y < x);
  }

  template <typename T>
  bool operator>= (result<T> const& x, result<T> const& y)
  {
    return !(x < y);
  }


// comparison with T

  template <typename T>
  bool operator== (result<T> const& lhs, T const& rhs)
  {
    return bool(lhs) ? static_cast<T>(lhs) == rhs : false;
  }

  template <typename T>
  bool operator== (T const& lhs, result<T> const& rhs)
  {
    return bool(rhs) ? lhs == static_cast<T>(rhs) : false;
  }

  template <typename T>
  bool operator!= (result<T> const& lhs, T const& rhs)
  {
    return bool(lhs) ? static_cast<T>(lhs) != rhs : true;
  }

  template <typename T>
  bool operator!= (T const& lhs, result<T> const& rhs)
  {
    return bool(rhs) ? lhs != static_cast<T>(rhs) : true;
  }

  template <typename T>
  bool operator< (result<T> const& lhs, T const& rhs)
  {
    return bool(lhs) ? static_cast<T>(lhs) < rhs : true;
  }

  template <typename T>
  bool operator< (T const& lhs, result<T> const& rhs)
  {
    return bool(rhs) ? lhs < static_cast<T>(rhs) : false;
  }

  template <typename T>
  bool operator> (T const& lhs, result<T> const& rhs)
  {
    return bool(lhs) ? static_cast<T>(rhs) < lhs : false;
  }

  template <typename T>
  bool operator> (result<T> const& lhs, T const& rhs)
  {
    return bool(lhs) ? rhs < static_cast<T>(lhs) : false;
  }

  template <typename T>
  bool operator<= (T const& lhs, result<T> const& rhs)
  {
    return bool(rhs) ? !(static_cast<T>(rhs) < lhs) : false;
  }

  template <typename T>
  bool operator<= (result<T> const& lhs, T const& rhs)
  {
    return bool(lhs) ? !(rhs < static_cast<T>(lhs)) : true;
  }

  template <typename T>
  bool operator>= (result<T> const& lhs, T const& rhs)
  {
    return bool(lhs) ? !(static_cast<T>(lhs) < rhs) : false;
  }

  template <typename T>
  bool operator>= (T const& lhs, result<T> const& rhs)
  {
    return bool(rhs) ? !(lhs < static_cast<T>(rhs)) : true;
  }

  template <typename T>
  void swap (result<T>& lhs, result<T>& rhs) noexcept(noexcept(lhs.swap(rhs)))
  {
    lhs.swap(rhs);
  }

  template <class T>
  inline result<std::decay_t<T>> make_result (T&& value)
  {
    return result<std::decay_t<T>>{std::forward<T>(value)};
  }

  template <class T, class... Args>
  inline result<T> make_result (Args&& ... args)
  {
    return result<T>{std::in_place, std::forward<Args>(args)...};
  }

  template <class T, class U, class... Args>
  inline result<T> make_result (std::initializer_list<U> ilist, Args&& ... args)
  {
    return result<T>{std::in_place, ilist, std::forward<Args>(args)...};
  }

  template <class T = void>
  inline result<T> make_result (std::error_code error)
  {
    return result<T>(std::move(error));
  }

  template <class T = void>
  inline result<T> make_result (std::exception_ptr excp)
  {
    return result<T>(std::move(excp));
  }
}

namespace std {
  template <typename T>
  struct tuple_size<algol::result<T>>
      : std::integral_constant<std::size_t, 1> {
  };

  template <typename T>
  struct tuple_element<0, algol::result<T>> { using type = const T&; };
}

#endif //ALGOL_RESULT_RESULT_HPP