#ifndef USER_DEFINED_LITERALS_H
#define USER_DEFINED_LITERALS_H

#include <cstdint>

#include "AbbreviatedTypes.h"

//Support for forcing user-defined literals to be evaluated at compile-time
template<unsigned long long sum, char... rest>
struct LiteralParser;

template<unsigned long long sum>
struct LiteralParser<sum>
{
    static const unsigned long long value = sum;
};

template<unsigned long long sum, char first, char... rest>
struct LiteralParser<sum, first, rest...>
{
    //TODO: Add support for parsing floating point values
    static_assert((first >= '0' && first <= '9'), "invalid input: expecting only numeric digits from 0-9");
    static const unsigned long long value = LiteralParser<sum * 10 + static_cast<unsigned long long>(first - '0'), rest...>::value;
};

//Add common fixed-width signed value literals
template<char... chars> constexpr i8 operator""_i8() { return {LiteralParser<0, chars...>::value}; }
template<char... chars> constexpr i16 operator""_i16() { return {LiteralParser<0, chars...>::value}; }
template<char... chars> constexpr i32 operator""_i32() { return {LiteralParser<0, chars...>::value}; }
template<char... chars> constexpr i64 operator""_i64() { return {LiteralParser<0, chars...>::value}; }

//Add common fixed-width unsigned value literals
template<char... chars> constexpr u8 operator""_u8() { return {LiteralParser<0, chars...>::value}; }
template<char... chars> constexpr u16 operator""_u16() { return {LiteralParser<0, chars...>::value}; }
template<char... chars> constexpr u32 operator""_u32() { return {LiteralParser<0, chars...>::value}; }
template<char... chars> constexpr u64 operator""_u64() { return {LiteralParser<0, chars...>::value}; }

//Add literals for ptrdiff_t and size_t
template<char... chars> constexpr isz operator""_isz() { return {LiteralParser<0, chars...>::value}; }
template<char... chars> constexpr usz operator""_usz() { return {LiteralParser<0, chars...>::value}; }

//Add support for floating point formats
constexpr f32 operator"" _f32(long double v) { return v; }
constexpr f64 operator"" _f64(long double v) { return v; }
constexpr f80 operator""_f80(long double v) { return v; }

constexpr f32 operator"" _f32(unsigned long long v) { return static_cast<double>(v); }
constexpr f64 operator"" _f64(unsigned long long v) { return static_cast<double>(v); }
constexpr f80 operator""_f80(unsigned long long v) { return static_cast<double>(v); }
#endif //USER_DEFINED_LITERALS_H
