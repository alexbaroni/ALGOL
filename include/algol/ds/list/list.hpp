#ifndef ALGOL_DS_LIST_HPP
#define ALGOL_DS_LIST_HPP

namespace algol { namespace ds {
    template<typename T>
    class list {
    public:


        virtual ~list() = default;
        list(list const&) = default;
        list& operator=(list const&) = default;
        list(list&&) = default;
        list& operator=(list&&) = default;
    };
}}
#endif //ALGOL_DS_LIST_HPP
