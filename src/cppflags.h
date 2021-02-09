#pragma once

// system includes
#include <type_traits>
#include <cstddef>
#include <utility>
#include <cstdint>

namespace cpputils {
class CppFlag
{
    using uint = unsigned int;
    using ushort = unsigned short;

    int i;
public:
    constexpr inline CppFlag(int value) noexcept : i(value) {}
    constexpr inline operator int() const noexcept { return i; }

    constexpr inline CppFlag(uint value) noexcept : i(int(value)) {}
    constexpr inline CppFlag(short value) noexcept : i(int(value)) {}
    constexpr inline CppFlag(ushort value) noexcept : i(int(uint(value))) {}
    constexpr inline operator uint() const noexcept { return uint(i); }
};

template<typename Enum>
class CppFlags
{
    static_assert((sizeof(Enum) <= sizeof(int)),
                      "CppFlags uses an int as storage, so an enum with underlying "
                      "long long will overflow.");
    static_assert((std::is_enum<Enum>::value), "CppFlags is only usable on enumeration types.");

    using uint = unsigned int;
    using ushort = unsigned short;

public:
    typedef typename std::conditional<
            std::is_unsigned<typename std::underlying_type<Enum>::type>::value,
            unsigned int,
            signed int
        >::type Int;

    typedef Enum enum_type;

    constexpr inline CppFlags() noexcept : i(0) {}
    constexpr inline CppFlags(Enum flags) noexcept : i(Int(flags)) {}

    constexpr inline CppFlags(CppFlag flag) noexcept : i(flag) {}

    constexpr inline CppFlags(std::initializer_list<Enum> flags) noexcept
        : i(initializer_list_helper(flags.begin(), flags.end())) {}

    constexpr inline CppFlags &operator&=(int mask) noexcept { i &= mask; return *this; }
    constexpr inline CppFlags &operator&=(uint mask) noexcept { i &= mask; return *this; }
    constexpr inline CppFlags &operator&=(Enum mask) noexcept { i &= Int(mask); return *this; }
    constexpr inline CppFlags &operator|=(CppFlags other) noexcept { i |= other.i; return *this; }
    constexpr inline CppFlags &operator|=(Enum other) noexcept { i |= Int(other); return *this; }
    constexpr inline CppFlags &operator^=(CppFlags other) noexcept { i ^= other.i; return *this; }
    constexpr inline CppFlags &operator^=(Enum other) noexcept { i ^= Int(other); return *this; }

    constexpr inline operator Int() const noexcept { return i; }

    constexpr inline CppFlags operator|(CppFlags other) const noexcept { return CppFlags(CppFlag(i | other.i)); }
    constexpr inline CppFlags operator|(Enum other) const noexcept { return CppFlags(CppFlag(i | Int(other))); }
    constexpr inline CppFlags operator^(CppFlags other) const noexcept { return CppFlags(CppFlag(i ^ other.i)); }
    constexpr inline CppFlags operator^(Enum other) const noexcept { return CppFlags(CppFlag(i ^ Int(other))); }
    constexpr inline CppFlags operator&(int mask) const noexcept { return CppFlags(CppFlag(i & mask)); }
    constexpr inline CppFlags operator&(uint mask) const noexcept { return CppFlags(CppFlag(i & mask)); }
    constexpr inline CppFlags operator&(Enum other) const noexcept { return CppFlags(CppFlag(i & Int(other))); }
    constexpr inline CppFlags operator~() const noexcept { return CppFlags(CppFlag(~i)); }

    constexpr inline bool operator!() const noexcept { return !i; }

    constexpr inline bool testFlag(Enum flag) const noexcept { return (i & Int(flag)) == Int(flag) && (Int(flag) != 0 || i == Int(flag) ); }
    constexpr inline CppFlags &setFlag(Enum flag, bool on = true) noexcept
    {
        return on ? (*this |= flag) : (*this &= ~Int(flag));
    }

private:
    constexpr static inline Int initializer_list_helper(typename std::initializer_list<Enum>::const_iterator it,
                                                               typename std::initializer_list<Enum>::const_iterator end)
    noexcept
    {
        return (it == end ? Int(0) : (Int(*it) | initializer_list_helper(it + 1, end)));
    }

    Int i;
};

class CppIncompatibleFlag
{
    int i;
public:
    constexpr inline explicit CppIncompatibleFlag(int i) noexcept;
    constexpr inline operator int() const noexcept { return i; }
};

constexpr inline CppIncompatibleFlag::CppIncompatibleFlag(int value) noexcept : i(value) {}
} // namespace cpputils

#define CPP_DECLARE_FLAGS(Flags, Enum)\
typedef ::cpputils::CppFlags<Enum> Flags;

#define CPP_DECLARE_INCOMPATIBLE_FLAGS(Flags) \
constexpr inline ::cpputils::CppIncompatibleFlag operator|(Flags::enum_type f1, int f2) noexcept \
{ return ::cpputils::CppIncompatibleFlag(int(f1) | f2); }

#define CPP_DECLARE_OPERATORS_FOR_FLAGS(Flags) \
constexpr inline ::cpputils::CppFlags<Flags::enum_type> operator|(Flags::enum_type f1, Flags::enum_type f2) noexcept \
{ return ::cpputils::CppFlags<Flags::enum_type>(f1) | f2; } \
constexpr inline ::cpputils::CppFlags<Flags::enum_type> operator|(Flags::enum_type f1, ::cpputils::CppFlags<Flags::enum_type> f2) noexcept \
{ return f2 | f1; } CPP_DECLARE_INCOMPATIBLE_FLAGS(Flags)
