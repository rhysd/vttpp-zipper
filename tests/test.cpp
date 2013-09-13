#include "../zipper/zipper.hpp"
#include "../zipper/make_pack.hpp"
#include "../zipper/aliases.hpp"

#include <type_traits>

#define STATIC_ASSERT_IMPL(expr) static_assert(expr, #expr)
#define STATIC_ASSERT(...)       STATIC_ASSERT_IMPL((__VA_ARGS__))
#define IS_SAME(...)             STATIC_ASSERT(std::is_same<__VA_ARGS__>::value)

using namespace zipper::alias;
namespace z = zipper;


template<int N>
struct n{
    using type = n<N>;
    static int const value = N;
};

template<int... Nums>
using int_seq = z::pack<n<Nums>...>;

using fib = int_seq<1, 2, 3, 5, 8, 13, 21, 34, 55, 89>;

STATIC_ASSERT(fib::size == 10);
IS_SAME(fib, fib::type);
IS_SAME(z::empty, z::pack<>);

IS_SAME(zipper_of<fib>, z::zipper<z::empty, fib>);
using fibz = zipper_of<fib>;

IS_SAME(pack_of<zipper_of<fib>>, fib);
IS_SAME(pack_of<emplace_zipper<int, double, char>>, z::pack<int, double, char>);
IS_SAME(prior<next<fibz>>, fibz);
IS_SAME(before<next<fibz>>, after<fibz>);
IS_SAME(insert_before<fibz, n<13>>, next<insert_after<fibz, n<13>>>);
IS_SAME(pack_of<insert_after<next<fibz>, n<13>>>, pack_of<insert_before<next<fibz>, n<13>>>);
IS_SAME(remove_after<fibz>, remove_before<next<fibz>>);
STATIC_ASSERT(z::is_begin<fibz>::value);
STATIC_ASSERT(! z::is_end<fibz>::value);
IS_SAME(advance<fibz, 3>, next<next<next<fibz>>>);
IS_SAME(retreat<advance<fibz, 3>, 3>, fibz);
IS_SAME(insert_all_before<fibz, int, double>, advance<insert_all_after<fibz, int, double>, 2>);
IS_SAME(swap<swap<next<fibz>>>, next<fibz>);
IS_SAME(swap<next<fibz>>, insert_before<prior<remove_after<next<fibz>>>, n<2>>);

#include <iostream>
int main()
{
    std::cout << "OK\n";
    return 0;
}
