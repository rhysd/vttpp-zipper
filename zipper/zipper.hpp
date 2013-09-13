#if !defined ZIPPER_ZIPPER_HPP_INCLUDED
#define      ZIPPER_ZIPPER_HPP_INCLUDED

#include <cstddef>
#include <type_traits>

#include "./pack.hpp"
#include "./detail/misc.hpp"

namespace zipper { 

using std::size_t;

template<class L, class R>
struct zipper;

template<class... Left, class... Right>
struct zipper<
           pack<Left...>,
           pack<Right...>
       >{
    using type = zipper<pack<Left...>, pack<Right...>>;
    using left = pack<Left...>;
    using right = pack<Right...>;
    static size_t const pos = left::size;
};


template<class P>
struct zipper_of
    : zipper<P, empty>
{};


template<class... Elems>
struct emplace_zipper
    : zipper<pack<Elems...>, empty>
{};


template<class Z>
struct before;

template<class LHead, class... LTail, class RightPack>
struct before<
           zipper<
               pack<LHead, LTail...>,
               RightPack
           >
       > : LHead
{};


template<class Z>
struct after;

template<class LeftPack, class RHead, class... RTail>
struct after<
           zipper<
               LeftPack,
               pack<RHead, RTail...>
           >
       > : RHead
{};


template<class Z>
struct next;

template<class LHead, class... LTail, class RHead, class... RTail>
struct next<
           zipper<
               pack<LHead, LTail...>,
               pack<RHead, RTail...>
           >
       > : zipper<
               pack<RHead, LHead, LTail...>,
               pack<RTail...>
           >
{};


template<class Z>
struct prior;

template<class LHead, class... LTail, class RHead, class... RTail>
struct prior<
           zipper<
               pack<LHead, LTail...>,
               pack<RHead, RTail...>
           >
       > : zipper<
               pack<LTail...>,
               pack<LHead, RHead, RTail...>
           >
{};


template<class Z, class T>
struct insert_before;

template<class... Left, class RightPack, class T>
struct insert_before<
           zipper<
               pack<Left...>,
               RightPack
           >,
           T
       > {
    using type = zipper<pack<T, Left...>, RightPack>;
};


template<class Z, class T>
struct insert_after;

template<class LeftPack, class... Right, class T>
struct insert_after<
           zipper<
               LeftPack,
               pack<Right...>
           >,
           T
       > {
    using type = zipper<
                     LeftPack,
                     pack<T, Right...>
                 >;
};


template<class Z>
struct remove_before;

template<class LHead, class... LTail, class RightPack>
struct remove_before<
           zipper<
               pack<LHead, LTail...>,
               RightPack
           >
       > {
    using type = zipper<
                     pack<LTail...>,
                     RightPack
                 >;
};


template<class Z>
struct remove_after;

template<class LeftPack, class RHead, class... RTail>
struct remove_after<
           zipper<
               LeftPack,
               pack<RHead, RTail...>
           >
       > {
    using type = zipper<
                     LeftPack,
                     pack<RTail...>
                 >;
};

// O(sizeof...(Z::left::size))
template<class Z>
struct pack_of;

template<class Left, class Right>
struct pack_of<zipper<Left, Right>>
    : detail::concat<
          typename detail::reverse<Left>::type,
          Right
      >::type
{};


template<class Z>
struct is_begin
    : std::false_type
{};

template<class Right>
struct is_begin<zipper<empty, Right>>
    : std::true_type
{};


template<class Z>
struct is_end
    : std::false_type
{};

template<class Left>
struct is_end<zipper<Left, empty>>
    : std::true_type
{};


// O(N)
template<class Z, size_t N>
struct advance
    : advance<next<Z>, N-1>
{};

template<class Z>
struct advance<Z, 0> : Z
{};


// O(N)
template<class Z, size_t N>
struct retreat
    : retreat<prior<Z>, N-1>
{};

template<class Z>
struct retreat<Z, 0> : Z
{};


// O(sizeof...(XS))
template<class Z, class... XS>
struct add_all_before;

template<class LeftPack, class RightPack, class... XS>
struct add_all_before<
           zipper<LeftPack, RightPack>,
           XS...
       > : zipper<
               typename detail::concat<
                   typename detail::reverse<pack<XS...>>::type,
                   LeftPack
               >::type,
               RightPack
           >
{};


template<class Z, class... XS>
struct add_all_after;

template<class LeftPack, class... Right, class... XS>
struct add_all_after<
           zipper<
               LeftPack,
               pack<Right...>
           >,
           XS...
       > : zipper<
               LeftPack,
               pack<XS..., Right...>
           >
{};


template<class Z>
struct swap;

template<class LHead, class...LTail, class RHead, class...RTail>
struct swap<
           zipper<
               pack<LHead, LTail...>,
               pack<RHead, RTail...>
           >
       > : zipper<
               pack<RHead, LTail...>,
               pack<LHead, RTail...>
           >
{};


} // namespace zipper

#endif    // ZIPPER_ZIPPER_HPP_INCLUDED
