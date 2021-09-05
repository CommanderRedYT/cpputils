#pragma once

// system includes
#include <string>
#include <optional>
#include <string_view>
#include <random>
#include <algorithm>

namespace cpputils {
inline std::string toString(bool val) { return val ? "true" : "false"; }
inline std::string toString(int8_t val) { return std::to_string(val); }
inline std::string toString(uint8_t val) { return std::to_string(val); }
inline std::string toString(int16_t val) { return std::to_string(val); }
inline std::string toString(uint16_t val) { return std::to_string(val); }
inline std::string toString(int32_t val) { return std::to_string(val); }
inline std::string toString(uint32_t val) { return std::to_string(val); }
inline std::string toString(int64_t val) { return std::to_string(val); }
inline std::string toString(uint64_t val) { return std::to_string(val); }
inline std::string toString(float val) { return std::to_string(val); }
inline std::string toString(double val) { return std::to_string(val); }
inline std::string toString(const std::string &val) { return val; }
inline std::string toString(std::optional<bool> val) { if (val) return toString(*val); else return {}; }
inline std::string toString(std::optional<int8_t> val) { if (val) return toString(*val); else return {}; }
inline std::string toString(std::optional<uint8_t> val) { if (val) return toString(*val); else return {}; }
inline std::string toString(std::optional<int16_t> val) { if (val) return toString(*val); else return {}; }
inline std::string toString(std::optional<uint16_t> val) { if (val) return toString(*val); else return {}; }
inline std::string toString(std::optional<int32_t> val) { if (val) return toString(*val); else return {}; }
inline std::string toString(std::optional<uint32_t> val) { if (val) return toString(*val); else return {}; }
inline std::string toString(std::optional<int64_t> val) { if (val) return toString(*val); else return {}; }
inline std::string toString(std::optional<uint64_t> val) { if (val) return toString(*val); else return {}; }
inline std::string toString(std::optional<float> val) { if (val) return toString(*val); else return {}; }
inline std::string toString(std::optional<double> val) { if (val) return toString(*val); else return {}; }
inline std::string toString(const std::optional<std::string> &val) { if (val) return toString(*val); else return {}; }

bool stringEqualsIgnoreCase(std::string_view a, std::string_view b);
bool stringStartsWith(std::string_view fullString, std::string_view begin);
bool stringEndsWith(std::string_view fullString, std::string_view ending);

//void stringReplaceAll(char search, char replace, std::string &subject);
void stringReplaceAll(char search, std::string_view replace, std::string &subject);
//void stringReplaceAll(std::string_view search, char replace, std::string &subject);
void stringReplaceAll(std::string_view search, std::string_view replace, std::string &subject);

//std::string stringReplaceAll(char search, char replace, std::string_view subject);
std::string stringReplaceAll(char search, std::string_view replace, std::string_view subject);
//std::string stringReplaceAll(std::string_view search, char replace, std::string_view subject);
std::string stringReplaceAll(std::string_view search, std::string_view replace, std::string_view subject);

template<typename Trandom>
std::string randomString(std::size_t length, Trandom &rng)
{
    constexpr const char chars[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::uniform_int_distribution dist{{}, std::size(chars) - 1};

    std::string result(length, '\0');
    std::generate_n(std::begin(result), length, [&]() { return chars[dist(rng)]; });
    return result;
}

} // namespace cpputils
