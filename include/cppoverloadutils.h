#pragma once

namespace cpputils {
template <typename... Args>
struct CppNonConstOverload
{
    template <typename R, typename T>
    constexpr auto operator()(R (T::*ptr)(Args...)) const noexcept -> decltype(ptr)
    { return ptr; }
    template <typename R, typename T>
    static constexpr auto of(R (T::*ptr)(Args...)) noexcept -> decltype(ptr)
    { return ptr; }
};
template <typename... Args>
struct CppConstOverload
{
    template <typename R, typename T>
    constexpr auto operator()(R (T::*ptr)(Args...) const) const noexcept -> decltype(ptr)
    { return ptr; }
    template <typename R, typename T>
    static constexpr auto of(R (T::*ptr)(Args...) const) noexcept -> decltype(ptr)
    { return ptr; }
};
template <typename... Args>
struct CppOverload : CppConstOverload<Args...>, CppNonConstOverload<Args...>
{
    using CppConstOverload<Args...>::of;
    using CppConstOverload<Args...>::operator();
    using CppNonConstOverload<Args...>::of;
    using CppNonConstOverload<Args...>::operator();
    template <typename R>
    constexpr auto operator()(R (*ptr)(Args...)) const noexcept -> decltype(ptr)
    { return ptr; }
    template <typename R>
    static constexpr auto of(R (*ptr)(Args...)) noexcept -> decltype(ptr)
    { return ptr; }
};

template <typename... Args> constexpr __attribute__((__unused__)) CppOverload<Args...> cppOverload = {};
template <typename... Args> constexpr __attribute__((__unused__)) CppConstOverload<Args...> cppConstOverload = {};
template <typename... Args> constexpr __attribute__((__unused__)) CppNonConstOverload<Args...> cppNonConstOverload = {};
} // namespace cpputils
