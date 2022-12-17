#pragma once

#include <type_traits>

/* concepts.h:
   Additional concepts to help with templates. */

BEGIN_LYO_NAMESPACE
template <typename Num>
concept Arithmetic = std::is_arithmetic_v<Num>;
END_LYO_NAMESPACE