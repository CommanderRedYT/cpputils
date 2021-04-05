#pragma once

// system includes
#include <string>
#include <optional>
#include <string_view>

namespace cpputils {
std::string toString(bool val);
std::string toString(int8_t val);
std::string toString(uint8_t val);
std::string toString(int16_t val);
std::string toString(uint16_t val);
std::string toString(int32_t val);
std::string toString(uint32_t val);
std::string toString(int64_t val);
std::string toString(uint64_t val);
std::string toString(float val);
std::string toString(double val);
std::string toString(const std::string &val);
std::string toString(std::optional<uint8_t> val);

bool stringEqualsIgnoreCase(std::string_view a, std::string_view b);
bool stringStartsWith(std::string_view fullString, std::string_view begin);
bool stringEndsWith(std::string_view fullString, std::string_view ending);
} // namespace cpputils
