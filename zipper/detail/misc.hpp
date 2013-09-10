#if !defined ZIPPER_DETAIL_REVERSE_HPP_INCLUDED
#define      ZIPPER_DETAIL_REVERSE_HPP_INCLUDED

namespace zipper {

// forward declaration
template<class... Elems>
struct pack;

namespace detail {

    template<class E, class P>
    struct append;

    template<class E, class... Elems>
    struct append<E, pack<Elems...>>
        : pack<Elems..., E>
    {};

    template<class P>
    struct reverse;

    template<class H, class... T>
    struct reverse<pack<H, T...>>
        : append<H, typename reverse<T...>::type>
    {};

    template<>
    struct reverse<pack<>>{
        using type = pack<>;
    };

    template<class T, class U>
    struct concat;

    template<class... TS, class... US>
    struct concat<pack<TS...>, pack<US...>>
        : pack<TS..., US...>
    {};

} // namespace detail
} // namespace zipper

#endif    // ZIPPER_DETAIL_REVERSE_HPP_INCLUDED
