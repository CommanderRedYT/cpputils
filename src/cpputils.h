#pragma once

// system includes
#include <utility>
#include <type_traits>
#include <algorithm>
#include <iterator>
#include <array>

namespace cpputils {
namespace literals {
/**
 * User-defined Literals
 *  usage:
 *
 *   uint32_t = test = 10_MHz; // --> 10000000
 */

constexpr unsigned long long operator"" _kHz(unsigned long long x)
{
    return x * 1000;
}

constexpr unsigned long long operator"" _MHz(unsigned long long x)
{
    return x * 1000 * 1000;
}

constexpr unsigned long long operator"" _GHz(unsigned long long x)
{
    return x * 1000 * 1000 * 1000;
}

constexpr unsigned long long operator"" _kBit(unsigned long long x)
{
    return x * 1024;
}

constexpr unsigned long long operator"" _MBit(unsigned long long x)
{
    return x * 1024 * 1024;
}

constexpr unsigned long long operator"" _GBit(unsigned long long x)
{
    return x * 1024 * 1024 * 1024;
}

constexpr unsigned long long operator"" _kB(unsigned long long x)
{
    return x * 1024;
}

constexpr unsigned long long operator"" _MB(unsigned long long x)
{
    return x * 1024 * 1024;
}

constexpr unsigned long long operator"" _GB(unsigned long long x)
{
    return x * 1024 * 1024 * 1024;
}
} // namespace literals

template<typename T>
T vmin(T&&t)
{
    return std::forward<T>(t);
}

template<typename T0, typename T1, typename... Ts>
typename std::common_type<T0, T1, Ts...>::type vmin(T0&& val1, T1&& val2, Ts&&... vs)
{
    if (val1 < val2)
        return vmin(val1, std::forward<Ts>(vs)...);
    else
        return vmin(val2, std::forward<Ts>(vs)...);
}
template<typename T>
T vmax(T&&t)
{
    return std::forward<T>(t);
}

template<typename T0, typename T1, typename... Ts>
typename std::common_type<T0, T1, Ts...>::type vmax(T0&& val1, T1&& val2, Ts&&... vs)
{
    if (val1 > val2)
        return vmax(val1, std::forward<Ts>(vs)...);
    else
        return vmax(val2, std::forward<Ts>(vs)...);
}

template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi )
{
    // assert( !(hi < lo) );
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

template<typename T>
T mapValue(T x, T in_min, T in_max, T out_min, T out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template<typename T>
T mapValueClamped(T x, T in_min, T in_max, T out_min, T out_max)
{
    if (x < std::min(in_min, in_max))
        x = std::min(in_min, in_max);
    else if (x > std::max(in_min, in_max))
        x = std::max(in_min, in_max);

    return mapValue(x, in_min, in_max, out_min, out_max);
}

template<typename First, typename ... T>
bool is_in(First &&first, T && ... t)
{
    return ((first == t) || ...);
}

template<typename BinaryPredicate, typename First, typename ... T>
bool is_in_predi(BinaryPredicate p, First &&first, T && ... t)
{
    return (p(first, t) || ...);
}

template<typename T>
[[nodiscard]] __attribute__ ((warn_unused_result)) constexpr inline __attribute__((__unused__)) bool fuzzyCompare(T p1, T p2);

template<>
[[nodiscard]] __attribute__ ((warn_unused_result)) constexpr inline __attribute__((__unused__)) bool fuzzyCompare<double>(double p1, double p2)
{
    return (std::abs(p1 - p2) * 1000000000000. <= std::min(std::abs(p1), std::abs(p2)));
}

template<>
[[nodiscard]] __attribute__ ((warn_unused_result)) constexpr inline __attribute__((__unused__)) bool fuzzyCompare<float>(float p1, float p2)
{
    return (std::abs(p1 - p2) * 100000.f <= std::min(std::abs(p1), std::abs(p2)));
}

template<typename T1, typename T2, typename Tcb>
void parallelForeach(T1 &container0, T2 &container1, Tcb &&callback)
{
    auto iter0 = std::begin(container0);
    auto iter1 = std::begin(container1);
    for (;
         iter0 != std::end(container0) && iter1 != std::cend(container1);
         iter0++, iter1++)
        callback(*iter0, *iter1);
}

template<typename T0, typename T1, typename T2, typename Tcb>
void parallelForeach(T0 &container0, T1 &container1, T2 &container2, Tcb &&callback)
{
    auto iter0 = std::begin(container0);
    auto iter1 = std::begin(container1);
    auto iter2 = std::begin(container2);
    for (;
         iter0 != std::end(container0) && iter1 != std::cend(container1) && iter2 != std::cend(container2);
         iter0++, iter1++, iter2++)
        callback(*iter0, *iter1, *iter2);
}

template<typename T0, typename T1, typename T2, typename T3, typename Tcb>
void parallelForeach(T0 &container0, T1 &container1, T2 &container2, T3 &container3, Tcb &&callback)
{
    auto iter0 = std::begin(container0);
    auto iter1 = std::begin(container1);
    auto iter2 = std::begin(container2);
    auto iter3 = std::begin(container3);
    for (;
         iter0 != std::end(container0) && iter1 != std::cend(container1) && iter2 != std::cend(container2) && iter3 != std::cend(container3);
         iter0++, iter1++, iter2++, iter3++)
        callback(*iter0, *iter1, *iter2, *iter3);
}

template<typename, template<typename...> class Ref>
struct is_specialization : std::false_type {};

template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref> : std::true_type {};

template<typename ...T>
constexpr bool is_specialization_v = is_specialization<T...>::value;

template<class T>
struct is_std_array : std::false_type {};

template<class T, size_t N>
struct is_std_array<std::array<T, N>> : std::true_type {};

template<class T>
constexpr bool is_std_array_v = is_std_array<std::remove_cvref_t<T>>::value;
} // namespace cpputils
