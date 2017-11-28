#ifndef ALGOL_IO_MANIP_HPP
#define ALGOL_IO_MANIP_HPP

#include <ios>

namespace algol::io {
  namespace {
    [[maybe_unused]] int compact_index ()
    {
      static int compact_index = std::ios_base::xalloc();
      return compact_index;
    }

    template<typename CharT, typename Traits>
    inline std::basic_ostream<CharT, Traits>& nocompact (std::basic_ostream<CharT, Traits>& os)
    {
      os.iword(compact_index()) = false;
      return os;
    }

    template<typename CharT, typename Traits>
    inline std::basic_ostream<CharT, Traits>& compact (std::basic_ostream<CharT, Traits>& os)
    {
      os.iword(compact_index()) = true;
      return os;
    }

    template<typename CharT, typename Traits>
    inline bool is_in_compact_format (std::basic_ostream<CharT, Traits>& os)
    {
      return static_cast<bool>(os.iword(compact_index()));
    }
  }
}

#endif //ALGOL_IO_MANIP_HPP
