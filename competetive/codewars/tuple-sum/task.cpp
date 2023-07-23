#include <tuple>
#include <type_traits>

template <typename T>
struct is_number : std::false_type {};

template <>
struct is_number<int> : std::true_type {};

template <>
struct is_number<double> : std::true_type {};

template <>
struct is_number<float> : std::true_type {};

template <typename... Ts>
double tuple_sum(const std::tuple<Ts...>& tpl)
{
    return 0;
}

template <typename T, typename... Ts>
double tuple_sum(const std::tuple<T, Ts...>& tpl)
{
    if constexpr (is_number<T>::value)
    {
        return std::get<0>(tpl) + tuple_sum(std::tuple<Ts...>(std::get<Ts>(tpl)...));
    }
    else
    {
        return tuple_sum(std::tuple<Ts...>(std::get<Ts>(tpl)...));
    }
}