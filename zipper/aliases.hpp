#if !defined ZIPPER_ALIASES_HPP_INCLUDED
#define      ZIPPER_ALIASES_HPP_INCLUDED

#include "./zipper.hpp"

namespace zipper {
namespace alias {

template<class Z>
using before = typename ::zipper::before<Z>::type;

template<class Z>
using after = typename ::zipper::after<Z>::type;

template<class Z>
using next = typename ::zipper::next<Z>::type;

template<class Z>
using prior = typename ::zipper::prior<Z>::type;

template<class... Elems>
using zipper_of = typename ::zipper::zipper_of<Elems...>::type;

template<class Z, class T>
using insert_before = typename ::zipper::insert_before<Z, T>::type;

template<class Z, class T>
using insert_after = typename ::zipper::insert_after<Z, T>::type;

template<class Z>
using remove_before = typename ::zipper::remove_before<Z>::type;

template<class Z>
using remove_after = typename ::zipper::remove_after<Z>::type;

template<class Z>
using pack_of = typename ::zipper::pack_of<Z>::type;

} // namespace alias
} // namespace zipper

#endif    // ZIPPER_ALIASES_HPP_INCLUDED
