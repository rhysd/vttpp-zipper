#if !defined ZIPPER_PACK_HPP_INCLUDED
#define      ZIPPER_PACK_HPP_INCLUDED

#include <cstddef>
#include <type_traits>

namespace zipper {

using std::size_t;

template<class... Elems>
struct pack {
    static const size_t size = sizeof...(Elems);
    using type = pack<Elems...>;
};


template<class... Args>
struct array_of{
    using value_type = typename std::decay<
                           typename std::common_type<
                               typename Args::type...
                           >::type
                       >::type;
    static value_type const value[sizeof...(Args)] = {Args::value...};
};


template<class P>
struct array_of_pack;

template<class... Elems>
struct array_of_pack<pack<Elems...>>
    : array_of<Elems...>
{};


using empty = pack<>;

} // namespace zipper

#endif    // ZIPPER_PACK_HPP_INCLUDED
