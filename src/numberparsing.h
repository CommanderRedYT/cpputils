#pragma once

// system includes
#include <cstdint>
#include <optional>
#include <cstdio>
#include <inttypes.h>

namespace cpputils {
template<typename T> constexpr std::optional<T> fromString(std::string_view str) = delete;

template<> constexpr inline std::optional<int8_t> fromString<int8_t>(std::string_view str)
{
    int8_t val{};
    if (std::sscanf(str.data(), "%" SCNi8, &val) == 1)
        return val;
    return std::nullopt;
}

template<> constexpr inline std::optional<uint8_t> fromString<uint8_t>(std::string_view str)
{
    uint8_t val{};
    if (std::sscanf(str.data(), "%" SCNu8, &val) == 1)
        return val;
    return std::nullopt;
}

template<> constexpr inline std::optional<int16_t> fromString<int16_t>(std::string_view str)
{
    int16_t val{};
    if (std::sscanf(str.data(), "%" SCNi16, &val) == 1)
        return val;
    return std::nullopt;
}

template<> constexpr inline std::optional<uint16_t> fromString<uint16_t>(std::string_view str)
{
    uint16_t val{};
    if (std::sscanf(str.data(), "%" SCNu16, &val) == 1)
        return val;
    return std::nullopt;
}

template<> constexpr inline std::optional<int32_t> fromString<int32_t>(std::string_view str)
{
    int32_t val{};
    if (std::sscanf(str.data(), "%" SCNi32, &val) == 1)
        return val;
    return std::nullopt;
}

template<> constexpr inline std::optional<uint32_t> fromString<uint32_t>(std::string_view str)
{
    uint32_t val{};
    if (std::sscanf(str.data(), "%" SCNu32, &val) == 1)
        return val;
    return std::nullopt;
}

template<> constexpr inline std::optional<int64_t> fromString<int64_t>(std::string_view str)
{
    int64_t val{};
    if (std::sscanf(str.data(), "%" SCNi64, &val) == 1)
        return val;
    return std::nullopt;
}

template<> constexpr inline std::optional<uint64_t> fromString<uint64_t>(std::string_view str)
{
    uint64_t val{};
    if (std::sscanf(str.data(), "%" SCNu64, &val) == 1)
        return val;
    return std::nullopt;
}
} // namespace cpputils
