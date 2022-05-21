#pragma once

// system includes
#include <string>

// 3rdparty lib includes
#include <tl/expected.hpp>
#include <fmt/core.h>

// local includes
#include "cppmacros.h"

// These macros make it possible to define a typesafe enum with parse and
// toString methods

#define DECLARE_TYPESAFE_ENUM_HELPER1(name, ...) name __VA_ARGS__ ,
#define DECLARE_TYPESAFE_ENUM_HELPER2(name, ...) case TheEnum::name: return #name;
#define DECLARE_TYPESAFE_ENUM_HELPER3(name, ...) else if (str == CPP_STRINGIFY(name)) return TheEnum::name;
#define DECLARE_TYPESAFE_ENUM_HELPER4(name, ...) cb(TheEnum::name, CPP_STRINGIFY(name));
namespace detail {
    template<typename T>
    constexpr bool isTypeSafeEnum(T) { return false; }

    template<typename T>
    struct IsTypeSafeEnumTrait {
        static constexpr bool value = isTypeSafeEnum(T{});
    };
} // namespace detail

template<typename T>
struct iterateEnum;

template <typename T>
constexpr bool IsTypeSafeEnum = detail::IsTypeSafeEnumTrait<T>::value;

#define DECLARE_TYPESAFE_ENUM(Name, Derivation, Values) \
    enum class Name Derivation \
    { \
        Values(DECLARE_TYPESAFE_ENUM_HELPER1) \
    }; \
    inline std::string toString(Name value) \
    { \
        switch (value) \
        { \
        using TheEnum = Name; \
        Values(DECLARE_TYPESAFE_ENUM_HELPER2) \
        } \
        return fmt::format("Unknown " #Name "({})", int(value)); \
    } \
    inline tl::expected<Name, std::string> parse##Name(std::string_view str) \
    { \
        using TheEnum = Name; \
        if (false) {} \
        Values(DECLARE_TYPESAFE_ENUM_HELPER3) \
        return tl::make_unexpected(fmt::format("invalid " #Name " ({})", str)); \
    } \
    template<typename T> \
    void iterate##Name(T &&cb) \
    { \
        using TheEnum = Name; \
        Values(DECLARE_TYPESAFE_ENUM_HELPER4) \
    }  \
    constexpr inline bool isTypeSafeEnum(Name) { return true; }  \
    template<> \
    struct iterateEnum<Name> { \
        template<typename T> \
        static void iterate(T&&cb) \
        { \
            return iterate##Name(std::forward<T>(cb)); \
        } \
    };

#define IMPLEMENT_TYPESAFE_ENUM(Name, Derivation, Values)
