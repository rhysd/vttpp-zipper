#if !defined ZIPPER_ZIPPER_HPP_INCLUDED
#define      ZIPPER_ZIPPER_HPP_INCLUDED

#include "./detail/misc.hpp"

namespace zipper { 
template<class... Elems>
struct pack {
    using type = pack<Elems...>;
};


using empty = pack<>;


template<class L, class R>
struct zipper;

template<class... Left, class... Right>
struct zipper<pack<Left...>, pack<Right...>>{
    using type = zipper<pack<Left...>, pack<Right...>>;
    using left = pack<Left...>;
    using right = pack<Right...>;
};


template<class Z>
struct before;

template<class LHead, class... LTail, class RightPack>
struct before<zipper<pack<LHead, LTail...>, RightPack>>
    : LHead
{};


template<class Z>
struct after;

template<class LeftPack, class RHead, class... RTail>
struct after<zipper<LeftPack, pack<RHead, RTail...>>>
    : RHead
{};


template<class Z>
struct next;

template<class LHead, class... LTail, class RHead, class... RTail>
struct next<zipper<pack<LHead, LTail...>, pack<RHead, RTail...>>>
    : zipper<pack<RHead, LHead, LTail...>, pack<RTail...>>
{};


template<class Z>
struct prior;

template<class LHead, class... LTail, class RHead, class... RTail>
struct prior<zipper<pack<LHead, LTail...>, pack<RHead, RTail...>>>
    : zipper<pack<LTail...>, pack<LHead, RHead, RTail...>>
{};


template<class... Elems>
struct zipper_of
    : zipper<pack<Elems...>, empty>
{};


template<class Z, class T>
struct insert_before;

template<class... Left, class RightPack, class T>
struct insert_before<zipper<pack<Left...>, RightPack>, T>{
    using type = zipper<pack<T, Left...>, RightPack>;
};


template<class Z, class T>
struct insert_after;

template<class LeftPack, class... Right, class T>
struct insert_after<zipper<LeftPack, pack<Right...>>, T>{
    using type = zipper<LeftPack, pack<T, Right...>>;
};


template<class Z>
struct remove_before;

template<class LHead, class... LTail, class RightPack>
struct remove_before<zipper<pack<LHead, LTail...>, RightPack>>{
    using type = zipper<pack<LTail...>, RightPack>;
};


template<class Z>
struct remove_after;

template<class LeftPack, class RHead, class... RTail>
struct remove_after<zipper<LeftPack, pack<RHead, RTail...>>>{
    using type = zipper<LeftPack, pack<RTail...>>;
};

template<class Z>
struct pack_of;

template<class Left, class Right>
struct pack_of<zipper<Left, Right>>
    : detail::concat<
          typename detail::reverse<Left>::type,
          Right
      >::type
{};


} // namespace zipper

#endif    // ZIPPER_ZIPPER_HPP_INCLUDED
