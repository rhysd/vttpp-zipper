#if !defined ZIPPER_MAKE_PACK_HPP_INCLUDED
#define      ZIPPER_MAKE_PACK_HPP_INCLUDED

#include <tuple>

namespace zipper {

template<class... Elems>
struct pack;

template<class L, class R>
struct zipper;

template<class P>
struct zipper_of;


template<class T>
struct make_pack;

template<class... Args>
struct make_pack<std::tuple<Args...>>
    : pack<Args...>
{};

template<class T>
struct make_zipper
    : zipper_of<make_pack<T>>
{};

} // namespace zipper

#endif    // ZIPPER_MAKE_PACK_HPP_INCLUDED
