#pragma once

// system includes
#include <string>
#include <string_view>
#include <array>

// 3rdparty lib includes
#include <tl/expected.hpp>

namespace cpputils {
struct ColorHelper
{
    constexpr ColorHelper() = default;
    constexpr ColorHelper(uint8_t _r, uint8_t _g, uint8_t _b) : r{_r}, g{_g}, b{_b} {}
    constexpr ColorHelper(const ColorHelper &other) = default;

    constexpr ColorHelper &operator=(const ColorHelper &other) = default;

    constexpr bool operator==(const ColorHelper &other) const { return r == other.r && g == other.g && b == other.b; }
    constexpr bool operator!=(const ColorHelper &other) const { return r != other.r || g != other.g || b != other.b; }

    uint8_t r{};
    uint8_t g{};
    uint8_t b{};
};

namespace {
constexpr ColorHelper black{};
constexpr ColorHelper red{255, 0, 0};
constexpr ColorHelper blue{0, 0, 255};
constexpr ColorHelper yellow{255, 255, 0};
constexpr ColorHelper cyan{0, 255, 255};
constexpr ColorHelper green{0, 255, 0};
constexpr ColorHelper white{255, 255, 255};
constexpr ColorHelper pink{255, 0, 255};
} // namespace

struct HsvColor
{
    constexpr HsvColor() = default;
    constexpr HsvColor(uint8_t _h, uint8_t _s, uint8_t _v) : h{_h}, s{_s}, v{_v}  {}
    constexpr HsvColor(const HsvColor &other) = default;

    constexpr HsvColor &operator=(const HsvColor &other) = default;

    constexpr bool operator==(const HsvColor &other) const { return h == other.h && s == other.s && v == other.v; }
    constexpr bool operator!=(const HsvColor &other) const { return h != other.h || s != other.s || v != other.v; }

    uint8_t h{};
    uint8_t s{};
    uint8_t v{};
};

std::string toString(ColorHelper color);
tl::expected<ColorHelper, std::string> parseColor(std::string_view str);

inline uint32_t colorToNumber(ColorHelper color)
{
    union {
        uint32_t temp;
        struct {
            // reverse order to be reverse compatible with existing configs
            uint8_t b;
            uint8_t g;
            uint8_t r;
            uint8_t x;
        };
    } helper;
    helper.b = color.b;
    helper.g = color.g;
    helper.r = color.r;
    helper.x = 0;
    return helper.temp;
}

inline ColorHelper numberToColor(uint32_t number)
{
    union {
        uint32_t temp;
        struct {
            // reverse order to be reverse compatible with existing configs
            uint8_t b;
            uint8_t g;
            uint8_t r;
            uint8_t x;
        };
    } helper;
    helper.temp = number;
    return ColorHelper{helper.r, helper.g, helper.b};
}

constexpr inline ColorHelper interpolateColor(ColorHelper left, ColorHelper right, uint8_t pos)
{
    int16_t leftAmount = pos;
    int16_t rightAmount = 255 - pos;

    return ColorHelper (
        (left.r * leftAmount / 255) + (right.r * rightAmount / 255),
        (left.g * leftAmount / 255) + (right.g * rightAmount / 255),
        (left.b * leftAmount / 255) + (right.b * rightAmount / 255)
    );
}

constexpr inline ColorHelper HsvToRgb(HsvColor hsv)
{
    if (hsv.s == 0)
        return ColorHelper{hsv.v, hsv.v, hsv.v};

    const uint8_t region = hsv.h / 43;
    const uint8_t remainder = (hsv.h - (region * 43)) * 6;

    const uint8_t p = (hsv.v * (255 - hsv.s)) >> 8;
    const uint8_t q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    const uint8_t t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
    case 0:  return ColorHelper{hsv.v, t,     p    };
    case 1:  return ColorHelper{q,     hsv.v, p    };
    case 2:  return ColorHelper{p,     hsv.v, t    };
    case 3:  return ColorHelper{p,     q,     hsv.v};
    case 4:  return ColorHelper{t,     p,     hsv.v};
    default: return ColorHelper{hsv.v, p,     q    };
    }
}

template<size_t COUNT>
constexpr inline std::array<ColorHelper, COUNT> generateRainbowColors()
{
    std::array<ColorHelper, COUNT> colors;

    for (int i = 0; i < COUNT; i++)
    {
        HsvColor hsvColor{uint8_t(i * 256.f / COUNT), 240, 255};
        ColorHelper rgbColor = HsvToRgb(hsvColor);
        colors[i] = rgbColor;
    }

    return colors;
}

} // namespace cpputils
