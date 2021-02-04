#pragma once

// system includes
#include <optional>
#include <string>

// local includes
#include "cppmacros.h"

// These two macros make it possible to define a typesafe enum with parse and
// toString methods

#define DECLARE_TYPESAFE_ENUM_HELPER1(name) name,
#define DECLARE_TYPESAFE_ENUM_HELPER2(name) case TheEnum::name: return #name;
#define DECLARE_TYPESAFE_ENUM_HELPER3(name) else if (str == CPP_STRINGIFY(name)) return TheEnum::name;

#define DECLARE_TYPESAFE_ENUM(Name, Derivation, Values) \
    enum class Name Derivation \
    { \
        Values(DECLARE_TYPESAFE_ENUM_HELPER1) \
    }; \
    std::string toString(Name value); \
    std::optional<Name> parse##Name(std::string_view str);

#define IMPLEMENT_TYPESAFE_ENUM(Name, Derivation, Values) \
    std::string toString(Name value) \
    { \
        switch (value) \
        { \
        using TheEnum = Name; \
        Values(DECLARE_TYPESAFE_ENUM_HELPER2) \
        } \
        return std::string{"Unknown " #Name "("} + std::to_string(int(value)) + ')'; \
    } \
    std::optional<Name> parse##Name(std::string_view str) \
    { \
    using TheEnum = Name; \
    if (false) {} \
    Values(DECLARE_TYPESAFE_ENUM_HELPER3) \
    return std::nullopt; \
    }
