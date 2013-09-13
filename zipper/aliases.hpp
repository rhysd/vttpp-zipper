#if !defined ZIPPER_ALIASES_HPP_INCLUDED
#define      ZIPPER_ALIASES_HPP_INCLUDED

#include <cstddef>

#include "./zipper.hpp"
#include "./make_pack.hpp"

namespace zipper {
namespace alias {

using std::size_t;

template<class Z>
using before = typename ::zipper::before<Z>::type;

template<class Z>
using after = typename ::zipper::after<Z>::type;

template<class Z>
using next = typename ::zipper::next<Z>::type;

template<class Z>
using prior = typename ::zipper::prior<Z>::type;

template<class P>
using zipper_of = typename ::zipper::zipper_of<P>::type;

template<class... Elems>
using emplace_zipper = typename ::zipper::emplace_zipper<Elems...>::type;

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

template<class Z, size_t N>
using advance = typename ::zipper::advance<Z, N>::type;

template<class Z, size_t N>
using retreat = typename ::zipper::retreat<Z, N>::type;

template<class Z, class...XS>
using insert_all_before = typename ::zipper::insert_all_before<Z, XS...>::type;

template<class Z, class...XS>
using insert_all_after = typename ::zipper::insert_all_after<Z, XS...>::type;

template<class Z>
using swap = typename swap<Z>::type;

template<class... Args>
using make_pack = typename make_pack<Args...>::type;

template<class T>
using make_zipper = typename make_zipper<T>::type;

} // namespace alias
} // namespace zipper

#endif    // ZIPPER_ALIASES_HPP_INCLUDED
