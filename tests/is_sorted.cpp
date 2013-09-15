#include <type_traits>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>

#include "../zipper/zipper.hpp"

namespace z = zipper;

template<int N>
struct n{
    using type = n<N>;
    static int const value = N;
};

template<int... Nums>
using int_seq = z::pack<n<Nums>...>;

template<class L, class R>
struct less{
    static bool const value = L::type::value < R::type::value;
    using type = std::integral_constant<bool, value>;
};

template<class Zipper>
struct zipper_is_sorted
    : std::conditional<
         z::is_end<Zipper>::value,
         std::true_type,
         boost::mpl::eval_if<
             less<
                 z::after<Zipper>,
                 z::before<Zipper>
             >,
             std::false_type,
             zipper_is_sorted<
                 typename boost::mpl::eval_if<
                    z::is_end<Zipper>,
                    z::zipper_of<z::empty>,
                    z::next<Zipper>
                 >::type
             >
         >
      >::type::type
{};

template<class Pack>
struct is_sorted
    : zipper_is_sorted<typename z::next<typename z::zipper_of<Pack>::type>::type>::type
{};

static_assert(is_sorted<int_seq<1, 3, 5, 6, 8, 9, 11, 23, 56>>::value, "");

#include <iostream>
int main() { std::cout << "OK\n"; return 0; }
