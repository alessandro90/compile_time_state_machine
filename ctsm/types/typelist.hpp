#ifndef CTSM_TYPELIST_HPP
#define CTSM_TYPELIST_HPP

namespace ctsm::tl
{
    template <typename... T>
    struct typelist_t
    {
    };

    template <typename T>
    struct typelist_t<T>
    {
        using type = T;
    };

    template <typename... T>
    struct head_t;

    template <typename T, typename... Ts>
    struct head_t<typelist_t<T, Ts...>>
    {
        using typelist = typelist_t<T>;
    };

    template <>
    struct head_t<typelist_t<>>
    {
        using typelist = typelist_t<>;
    };

    template <typename... T>
    struct tail_t;

    template <typename T, typename... Ts>
    struct tail_t<typelist_t<T, Ts...>>
    {
        using typelist = typelist_t<Ts...>;
    };

    template <>
    struct tail_t<typelist_t<>>
    {
        using typelist = typelist_t<>;
    };
}
#endif
