#pragma once

// system includes
#include <cstdint>

namespace cpputils {
template<typename X> struct RefWhenNeeded      { using T = const X &;     RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<bool>          { using T = bool;          RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<int8_t>        { using T = int8_t;        RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<uint8_t>       { using T = uint8_t;       RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<int16_t>       { using T = int16_t;       RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<uint16_t>      { using T = uint16_t;      RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<int32_t>       { using T = int32_t;       RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<uint32_t>      { using T = uint32_t;      RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<int64_t>       { using T = int64_t;       RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<uint64_t>      { using T = uint64_t;      RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<long>          { using T = long;          RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<unsigned long> { using T = unsigned long; RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<float>         { using T = float;         RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
template<> struct RefWhenNeeded<double>        { using T = double;        RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };

//template<typename X> struct RefWhenNeeded                       { using T = X;                                      RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
//template<> struct RefWhenNeeded<JsonObjectConst>                { using T = const JsonObjectConst &;                RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
//template<> struct RefWhenNeeded<std::optional<JsonObjectConst>> { using T = const std::optional<JsonObjectConst> &; RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
//template<> struct RefWhenNeeded<JsonArrayConst>                 { using T = const JsonArrayConst &;                 RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
//template<> struct RefWhenNeeded<JsonVariantConst>               { using T = const JsonVariantConst &;               RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
//template<> struct RefWhenNeeded<std::string>                    { using T = const std::string &;                    RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
//template<> struct RefWhenNeeded<std::optional<uint32_t>>        { using T = const std::optional<uint32_t> &;        RefWhenNeeded() = delete; ~RefWhenNeeded() = delete; };
} // namespace cpputils
