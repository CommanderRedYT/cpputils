#pragma once

// system includes
#include <optional>
#include <string>

// local includes
#include "cppmacros.h"

#define CPPTYPESAFEENUM_SHOULD_INLINE

// These two macros make it possible to define a typesafe enum with parse and
// toString methods

#define DECLARE_TYPESAFE_ENUM_HELPER1(name) name,
#define DECLARE_TYPESAFE_ENUM_HELPER2(name) case TheEnum::name: return #name;
#define DECLARE_TYPESAFE_ENUM_HELPER3(name) else if (str == CPP_STRINGIFY(name)) return TheEnum::name;
#define DECLARE_TYPESAFE_ENUM_HELPER4(name) cb(TheEnum::name, CPP_STRINGIFY(name));

#ifdef CPPTYPESAFEENUM_SHOULD_INLINE
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
        return std::string{"Unknown " #Name "("} + std::to_string(int(value)) + ')'; \
    } \
    inline std::optional<Name> parse##Name(std::string_view str) \
    { \
        using TheEnum = Name; \
        if (false) {} \
        Values(DECLARE_TYPESAFE_ENUM_HELPER3) \
        return std::nullopt; \
    } \
    template<typename T> \
    void iterate##Name(T &&cb) \
    { \
        using TheEnum = Name; \
        Values(DECLARE_TYPESAFE_ENUM_HELPER4) \
    }

#define IMPLEMENT_TYPESAFE_ENUM(Name, Derivation, Values)
#else
#define DECLARE_TYPESAFE_ENUM(Name, Derivation, Values) \
    enum class Name Derivation \
    { \
        Values(DECLARE_TYPESAFE_ENUM_HELPER1) \
    }; \
    std::string toString(Name value); \
    std::optional<Name> parse##Name(std::string_view str); \
    template<typename T> \
    void iterate##Name(T &&cb) \
    { \
        using TheEnum = Name; \
        Values(DECLARE_TYPESAFE_ENUM_HELPER4) \
    }

#define IMPLEMENT_TYPESAFE_ENUM(Name, Derivation, Values) \
    ExportPrefix std::string toString(Name value) \
    { \
        switch (value) \
        { \
        using TheEnum = Name; \
        Values(DECLARE_TYPESAFE_ENUM_HELPER2) \
        } \
        return std::string{"Unknown " #Name "("} + std::to_string(int(value)) + ')'; \
    } \
    ExportPrefix std::optional<Name> parse##Name(std::string_view str) \
    { \
        using TheEnum = Name; \
        if (false) {} \
        Values(DECLARE_TYPESAFE_ENUM_HELPER3) \
        return std::nullopt; \
    }
#endif
