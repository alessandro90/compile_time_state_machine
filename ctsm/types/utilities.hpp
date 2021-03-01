#ifndef CTSM_UTILITIES_HPP
#define CTSM_UTILITIES_HPP

#include <type_traits>

namespace ctsm::utils
{
    template <typename T1, typename T2>
    struct is_different
    {
        inline static constexpr bool value = !std::is_same_v<T1, T2>;
    };

    template <typename...>
    struct unique_t;

    template <typename T, typename... Types>
    struct unique_t<T, Types...>
    {
        inline static constexpr bool value = std::conjunction_v<is_different<T, Types>...> &&
                                             unique_t<Types...>::value;
    };

    template <typename T>
    struct unique_t<T> : std::true_type
    {
    };

    template <>
    struct unique_t<> : std::true_type
    {
    };

    template <typename...>
    struct is_simple_type_t;

    template <typename T>
    struct is_simple_type_t<T>
    {
        inline static constexpr bool value = std::is_same_v<std::decay_t<T>, T>;
    };

    template <>
    struct is_simple_type_t<> : public std::true_type
    {
    };
}
#endif
