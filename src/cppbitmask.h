#pragma once

// system includes
#include <cstdint>
#include <type_traits>
#include <cassert>

// forward declarations
class TstCppBitmask;

namespace cpputils {
template<std::size_t BITS_COUNT>
class bit_pattern
{
    friend class ::TstCppBitmask;

public:
    using value_t = std::uint32_t; // TODO make dependant to BITS_COUNT

    constexpr bit_pattern(const char (&input)[BITS_COUNT+1])
    {
        value_t cur_bit = (1 << (BITS_COUNT - 1));
        for (const char val : input)
        {
            switch (val)
            {
            case '\0':
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

    constexpr bool match(const value_t value) const
    {
        return (value & mask) == expected;
    }

    constexpr friend bool operator==(const bit_pattern &l, const bit_pattern &r)
    {
        return l.expected == r.expected &&
               l.mask     == r.mask;
    }

private:
    value_t expected{};
    value_t mask{};
};
} // namespace cpputils
