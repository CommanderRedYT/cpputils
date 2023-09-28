#include "color_utils.h"

// system includes
#include <cstdio>

// 3rdparty lib includes
#include <fmt/core.h>

namespace cpputils {
std::string toString(ColorHelper color)
{
    return fmt::format("#{:02X}{:02X}{:02X}", color.r, color.g, color.b);
}

std::expected<ColorHelper, std::string> parseColor(std::string_view str)
{
    // input may be "#FFF" or "#FFFFFF" or "#FFFFFFFF"

    if (ColorHelper helper; std::sscanf(str.data(), "#%2hhx%2hhx%2hhx", &helper.r, &helper.g, &helper.b) == 3)
        return helper;

    if (ColorHelper helper; std::sscanf(str.data(), "#%1hhx%1hhx%1hhx", &helper.r, &helper.g, &helper.b) == 3)
    {
        // #F00 -> #FF0000
        helper.r *= 0x11;
        helper.g *= 0x11;
        helper.b *= 0x11;
        return helper;
    }

    return std::unexpected(fmt::format("invalid color {}", str));
}

} // namespace cpputils
