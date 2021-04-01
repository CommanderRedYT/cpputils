#pragma once

// system includes
#include <cstdint>
#include <type_traits>
#include <cassert>

// forward declarations
class TstCppBitmask;

namespace cpputils {
template<typename T>
class basic_bit_pattern
{
    friend class ::TstCppBitmask;
    T expected{};
    T mask{};

public:
    template<std::size_t Size>
    constexpr basic_bit_pattern(const char (&input)[Size])
    {
        T cur_bit = (1 << (Size - 2));
        for (const char val : input)
        {
            switch (val)
            {
            case 0:
                return;
            case '1':
                expected |= cur_bit;
            [[fallthrough]];
            case '0':
                mask |= cur_bit;
                break;
            case 'x':
            case 'X':
                break;
            default:
                assert("Unknown characters in bit pattern input" && 0);
            }

            cur_bit >>= 1;
        }
    }

    constexpr bool match(const T value) const
    {
        return (value & mask) == expected;
    }

    constexpr friend bool operator==(const basic_bit_pattern &l, const basic_bit_pattern &r)
    {
        return l.expected == r.expected &&
               l.mask     == r.mask;
    }
};

using bit_pattern = basic_bit_pattern<std::uint32_t>;
} // namespace cpputils
