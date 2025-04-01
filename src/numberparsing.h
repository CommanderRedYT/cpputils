#pragma once

// system includes
#include <cstdint>
#include <cstdio>
#include <expected>
#include <format>
#include <inttypes.h>
#include <string>

namespace cpputils {
template<typename T> std::expected<T, std::string> fromString(std::string_view str) = delete;

template<> inline std::expected<int8_t, std::string> fromString<int8_t>(std::string_view str)
{
    int8_t val;
    if (std::sscanf(str.data(), "%" SCNi8, &val) != 1)
        return std::unexpected(fmt::format("invalid int8_t {}", str));
    return val;
}

template<> inline std::expected<uint8_t, std::string> fromString<uint8_t>(std::string_view str)
{
    uint8_t val;
    if (std::sscanf(str.data(), "%" SCNu8, &val) != 1)
        return std::unexpected(fmt::format("invalid uint8_t {}", str));
    return val;
}

template<> inline std::expected<int16_t, std::string> fromString<int16_t>(std::string_view str)
{
    int16_t val;
    if (std::sscanf(str.data(), "%" SCNi16, &val) != 1)
        return std::unexpected(fmt::format("invalid int16_t {}", str));
    return val;
}

template<> inline std::expected<uint16_t, std::string> fromString<uint16_t>(std::string_view str)
{
    uint16_t val;
    if (std::sscanf(str.data(), "%" SCNu16, &val) != 1)
        return std::unexpected(fmt::format("invalid uint16_t {}", str));
    return val;
}

template<> inline std::expected<int32_t, std::string> fromString<int32_t>(std::string_view str)
{
    int32_t val;
    if (std::sscanf(str.data(), "%" SCNi32, &val) != 1)
        return std::unexpected(fmt::format("invalid int32_t {}", str));
    return val;
}

template<> inline std::expected<uint32_t, std::string> fromString<uint32_t>(std::string_view str)
{
    uint32_t val;
    if (std::sscanf(str.data(), "%" SCNu32, &val) != 1)
        return std::unexpected(fmt::format("invalid uint32_t {}", str));
    return val;
}

#ifdef ESP_PLATFORM
template<> inline std::expected<int, std::string> fromString<int>(std::string_view str)
{
    int val;
    if (std::sscanf(str.data(), "%i", &val) != 1)
        return std::unexpected(fmt::format("invalid int {}", str));
    return val;
}

template<> inline std::expected<unsigned int, std::string> fromString<unsigned int>(std::string_view str)
{
    unsigned int val;
    if (std::sscanf(str.data(), "%u", &val) != 1)
        return std::unexpected(fmt::format("invalid unsigned int {}", str));
    return val;
}
#endif

template<> inline std::expected<int64_t, std::string> fromString<int64_t>(std::string_view str)
{
    int64_t val;
    if (std::sscanf(str.data(), "%" SCNi64, &val) != 1)
        return std::unexpected(fmt::format("invalid int64_t {}", str));
    return val;
}

template<> inline std::expected<uint64_t, std::string> fromString<uint64_t>(std::string_view str)
{
    uint64_t val;
    if (std::sscanf(str.data(), "%" SCNu64, &val) != 1)
        return std::unexpected(fmt::format("invalid uint64_t {}", str));
    return val;
}

template<> inline std::expected<float, std::string> fromString<float>(std::string_view str)
{
    float val;
    if (std::sscanf(str.data(), "%f", &val) != 1)
        return std::unexpected(fmt::format("invalid float {}", str));
    return val;
}

template<> inline std::expected<double, std::string> fromString<double>(std::string_view str)
{
    double val;
    if (std::sscanf(str.data(), "%lf", &val) != 1)
        return std::unexpected(fmt::format("invalid double {}", str));
    return val;
}
} // namespace cpputils
