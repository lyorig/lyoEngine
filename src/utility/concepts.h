#pragma once

#include <type_traits>
#include "../macros.h"

/* concepts.h:
   Additional concepts to help with templates. */

BEGIN_LYO_NAMESPACE
template <typename Num>
concept Arithmetic = std::is_arithmetic_v<Num>;

template <typename Char>
concept Character =
std::is_same_v<Char, char> ||
std::is_same_v<Char, signed char> ||
std::is_same_v<Char, unsigned char> ||
std::is_same_v<Char, wchar_t> ||
std::is_same_v<Char, char8_t> ||
std::is_same_v<Char, char16_t> ||
std::is_same_v<Char, char32_t>;

template <typename Arr>
concept Array = std::is_array_v<Arr>;

template <typename Ptr>
concept Pointer = std::is_pointer_v<Ptr>;

END_LYO_NAMESPACE