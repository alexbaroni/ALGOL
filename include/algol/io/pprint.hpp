#ifndef ALGOL_IO_PPRINT_HPP
#define ALGOL_IO_PPRINT_HPP

#include <string>
#include <iostream>
#include <type_traits>
#include <iterator>
#include <utility>

#include <string>
#include <iostream>
#include <type_traits>
#include <iterator>
#include <utility>

#define PPRINT_DEFAULT_DECORATION(TYPE, PREFIX, DELIM, POSTFIX, ...) \
    namespace algol { namespace io { \
        namespace pprint { template<__VA_ARGS__>\
        struct defaulted<TYPE> {\
        static decor<TYPE> decoration() {\
          return { PREFIX, DELIM, POSTFIX };\
        } /*decoration*/ }; /*defaulted*/}}} /*algol::io::pprint*/

#define PPRINT_DEFAULT_WDECORATION(TYPE, PREFIX, DELIM, POSTFIX, ...) \
    namespace algol { namespace io { \
        namespace pprint { template<__VA_ARGS__>\
        struct defaulted<TYPE, wchar_t, std::char_traits<wchar_t>> {\
        static decor<TYPE, wchar_t, std::char_traits<wchar_t>> decoration(){\
          return { PREFIX, DELIM, POSTFIX };\
        } /*decoration*/ }; /*defaulted*/}}} /*algol::io::pprint*/

namespace algol::io::pprint {
  namespace detail {
    // drag in begin and end overloads
    using std::begin;
    using std::end;
    // helper template
    template <int I> using _ol = std::integral_constant<int, I>*;

    // SFINAE check whether T is a range with begin/end
    template <class T>
    class is_range {
      // helper function declarations using expression sfinae
      template <class U, _ol<0> = nullptr>
      static std::false_type b (...);
      template <class U, _ol<1> = nullptr>
      static auto b (U& v) -> decltype(begin(v), std::true_type());
      template <class U, _ol<0> = nullptr>
      static std::false_type e (...);
      template <class U, _ol<1> = nullptr>
      static auto e (U& v) -> decltype(end(v), std::true_type());
      // return types
      using b_return = decltype(b<T>(std::declval<T&>()));
      using e_return = decltype(e<T>(std::declval<T&>()));
    public:
      static const bool value = b_return::value && e_return::value;
    };
  }

  // holder class for data
  template <class T, class CharT = char, class TraitT = std::char_traits<CharT>>
  struct decor {
    static const int xindex;
    std::basic_string<CharT, TraitT> prefix, delimiter, postfix;

    decor (std::basic_string<CharT, TraitT> const& pre = "",
           std::basic_string<CharT, TraitT> const& delim = "",
           std::basic_string<CharT, TraitT> const& post = "")
        : prefix(pre), delimiter(delim), postfix(post)
    {}
  };

  template <class T, class charT, class traits>
  int const decor<T, charT, traits>::xindex = std::ios_base::xalloc();

  namespace detail {
    template <class T, class CharT, class TraitT>
    void manage_decor (std::ios_base::event evt, std::ios_base& s, int const idx)
    {
      using deco_type = decor<T, CharT, TraitT>;
      if (evt == std::ios_base::erase_event) { // erase deco
        void const* const p = s.pword(idx);
        if (p) {
          //TODO undestand why have to remove trailing const
          //delete static_cast<deco_type const* const>(p);
          delete static_cast<deco_type const*>(p);
          s.pword(idx) = nullptr;
        }
      }
      else if (evt == std::ios_base::copyfmt_event) { // copy deco
        void const* const p = s.pword(idx);
        if (p) {
          //TODO undestand why have to remove trailing const
          //auto np = new deco_type {*static_cast<deco_type const* const>(p)};
          auto np = new deco_type {*static_cast<deco_type const*>(p)};
          s.pword(idx) = static_cast<void*>(np);
        }
      }
    }

    template <class T>
    struct clearer {
    };

    template <class T, class CharT, class TraitT>
    std::basic_ostream<CharT, TraitT>& operator<< (std::basic_ostream<CharT, TraitT>& s, clearer<T> const&)
    {
      using deco_type = decor<T, CharT, TraitT>;
      void const* const p = s.pword(deco_type::xindex);
      if (p) { // delete if set
        delete static_cast<deco_type const*>(p);
        s.pword(deco_type::xindex) = nullptr;
      }

      return s;
    }

    template <class CharT, class TraitT = std::char_traits<CharT>>
    struct default_data {
      static inline std::basic_string<CharT, TraitT> prefix ()
      { return {""}; }

      static inline std::basic_string<CharT, TraitT> delimiter ()
      { return {", "}; }

      static inline std::basic_string<CharT, TraitT> postfix ()
      { return {""}; }
    };

    template <>
    struct default_data<wchar_t, std::char_traits<wchar_t>> {
      using CT = std::char_traits<wchar_t>;

      static inline std::basic_string<wchar_t, CT> prefix ()
      { return {L""}; }

      static inline std::basic_string<wchar_t, CT> delimiter ()
      { return {L", "}; }

      static inline std::basic_string<wchar_t, CT> postfix ()
      { return {L""}; }
    };
  }

  // Clear decoration for T
  template <class T>
  detail::clearer<T> clear ()
  { return {}; }

  template <class T, class CharT, class TraitT>
  void clear (std::basic_ostream<CharT, TraitT>& s)
  { s << detail::clearer<T>{}; }

  // impose decoration on ostream
  template <class T, class CharT, class TraitT>
  std::basic_ostream<CharT, TraitT>& operator<< (std::basic_ostream<CharT, TraitT>& s, decor<T, CharT, TraitT>&& h)
  {
    using deco_type = decor<T, CharT, TraitT>;
    void const* const p = s.pword(deco_type::xindex);
    // delete if already set
    if (p) delete static_cast<decor<T, CharT, TraitT> const*>(p);
    s.pword(deco_type::xindex) = static_cast<void*>(new deco_type {std::move(h)});
    // check whether we already have a callback registered
    if (s.iword(deco_type::xindex) == 0) { // if this is not the case register callback and set iword
      s.register_callback(detail::manage_decor<T, CharT, TraitT>, deco_type::xindex);
      s.iword(deco_type::xindex) = 1;
    }

    return s;
  }

  template <class T, class CharT = char, class TraitT = std::char_traits<CharT>>
  struct defaulted {
    static inline decor<T, CharT, TraitT> decoration ()
    {
      return {detail::default_data<CharT, TraitT>::prefix(),
              detail::default_data<CharT, TraitT>::delimiter(),
              detail::default_data<CharT, TraitT>::postfix()};
    }
  };

  template <class T, class CharT = char, class TraitT = std::char_traits<CharT>>
  decor<T, CharT, TraitT> decoration (std::basic_string<CharT, TraitT> const& prefix,
                                      std::basic_string<CharT, TraitT> const& delimiter,
                                      std::basic_string<CharT, TraitT> const& postfix)
  {
    return {prefix, delimiter, postfix};
  }

  template <class T, class CharT = char, class TraitT = std::char_traits<CharT>>
  decor<T, CharT, TraitT> decoration (std::basic_string<CharT, TraitT> const& delimiter)
  {
    return {defaulted<T, CharT, TraitT>::decoration().prefix,
            delimiter, defaulted<T, CharT, TraitT>::decoration().postfix};
  }

  template <class T, class CharT = char, class TraitT = std::char_traits<CharT>>
  decor<T, CharT, TraitT> decoration (CharT const* const prefix,
                                      CharT const* const delimiter, CharT const* const postfix)
  {
    using str_type = std::basic_string<CharT, TraitT>;
    return {str_type{prefix}, str_type{delimiter}, str_type{postfix}};
  }

  template <class T, class CharT = char, class TraitT = std::char_traits<CharT>>
  decor<T, CharT, TraitT> decoration (CharT const* const delimiter)
  {
    using str_type = std::basic_string<CharT, TraitT>;
    return {defaulted<T, CharT, TraitT>::decoration().prefix,
            str_type{delimiter}, defaulted<T, CharT, TraitT>::decoration().postfix};
  }

  template <typename T, std::size_t N, std::size_t L>
  struct tuple {
    template <class CharT, class TraitT>
    static void print (std::basic_ostream<CharT, TraitT>& s, T const& value,
                       std::basic_string<CharT, TraitT> const& delimiter)
    {
      s << std::get<N>(value) << delimiter;
      tuple<T, N + 1, L>::print(s, value, delimiter);
    }
  };

  template <typename T, std::size_t N>
  struct tuple<T, N, N> {
    template <class CharT, class TraitT>
    static void print (std::basic_ostream<CharT, TraitT>& s, T const& value,
                       std::basic_string<CharT, TraitT> const&)
    {
      s << std::get<N>(value);
    }
  };
}

template <class CharT, class TraitT>
std::basic_ostream<CharT, TraitT>& operator<< (std::basic_ostream<CharT, TraitT>& s, std::tuple<> const&)
{
  using deco_type = algol::io::pprint::decor<std::tuple<void*>, CharT, TraitT>;
  using defaulted_type = algol::io::pprint::defaulted<std::tuple<void*>, CharT, TraitT>;
  void const* const p = s.pword(deco_type::xindex);
  auto const d = static_cast<deco_type const* const>(p);
  s << (d ? d->prefix : defaulted_type::decoration().prefix);
  s << (d ? d->postfix : defaulted_type::decoration().postfix);
  return s;
}

template <class CharT, class TraitT, class ... T>
std::basic_ostream<CharT, TraitT>& operator<< (std::basic_ostream<CharT, TraitT>& s, std::tuple<T...> const& v)
{
  using deco_type = algol::io::pprint::decor<std::tuple<void*>, CharT, TraitT>;
  using defaulted_type = algol::io::pprint::defaulted<std::tuple<void*>, CharT, TraitT>;
  using pprint_tuple = algol::io::pprint::tuple<std::tuple<T...>, 0U, sizeof...(T) - 1U>;
  void const* const p = s.pword(deco_type::xindex);
  auto const d = static_cast<deco_type const* const>(p);
  s << (d ? d->prefix : defaulted_type::decoration().prefix);
  pprint_tuple::print(s, v, d ? d->delimiter : defaulted_type::decoration().delimiter);
  s << (d ? d->postfix : defaulted_type::decoration().postfix);
  return s;
}

template <class T, class U, class CharT, class TraitT>
std::basic_ostream<CharT, TraitT>& operator<< (std::basic_ostream<CharT, TraitT>& s, std::pair<T, U> const& v)
{
  using deco_type = algol::io::pprint::decor<std::pair<T, U>, CharT, TraitT>;
  using defaulted_type = algol::io::pprint::defaulted<std::pair<T, U>, CharT, TraitT>;
  //TODO undestand why have to remove trailing const
//  void const* const p = s.pword(deco_type::xindex);
//  auto const d = static_cast<deco_type const* const>(p);
  auto const d = static_cast<deco_type const*>(s.pword(deco_type::xindex));
  s << (d ? d->prefix : defaulted_type::decoration().prefix);
  s << v.first;
  s << (d ? d->delimiter : defaulted_type::decoration().delimiter);
  s << v.second;
  s << (d ? d->postfix : defaulted_type::decoration().postfix);
  return s;
}

template <class T, class CharT = char, class TraitT = std::char_traits<CharT>>
typename std::enable_if<algol::io::pprint::detail::is_range<T>::value,
    std::basic_ostream<CharT, TraitT>>::type& operator<< (std::basic_ostream<CharT, TraitT>& s, T const& v)
{
  bool first(true);
  using deco_type = algol::io::pprint::decor<T, CharT, TraitT>;
  using default_type = algol::io::pprint::defaulted<T, CharT, TraitT>;
  //TODO undestand why have to remove trailing const
//  void const* const p = s.pword(deco_type::xindex);
//  auto d = static_cast<algol::io::pprint::decor<T, CharT, TraitT> const* const>(p);
  auto d = static_cast<algol::io::pprint::decor<T, CharT, TraitT> const*>(s.pword(deco_type::xindex));
  s << (d ? d->prefix : default_type::decoration().prefix);
  for (auto const& e : v) { // v is range thus range based for works
    if (!first) s << (d ? d->delimiter : default_type::decoration().delimiter);
    s << e;
    first = false;
  }
  s << (d ? d->postfix : default_type::decoration().postfix);
  return s;
}

#endif // ALGOL_IO_PPRINT_HPP

