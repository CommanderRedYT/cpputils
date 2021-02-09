#pragma once

#include <string_view>

namespace cpputils {
bool stringEqualsIgnoreCase(std::string_view a, std::string_view b);
bool stringStartsWith(std::string_view fullString, std::string_view begin);
bool stringEndsWith(std::string_view fullString, std::string_view ending);
} // namespace cpputils
