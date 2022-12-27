#pragma once

#include <SDL_pixels.h>
#include <concepts>
#include "concepts.h"

/* algorithms.h:
   Simple functions which don't fit elsewhere. */

BEGIN_LYO_NAMESPACE
/* Various type-casting functions. */
namespace Cast
{
	/* Cast from a floating-point to an integral, with proper rounding. */
	template <std::integral Cast_to, std::floating_point Cast_from>
	constexpr Cast_to Signed(const Cast_from x) noexcept
	{
		return SC<Cast_to>(x + (x >= 0 ? 0.5 : -0.5));
	}

	/* Cast from a floating-point to an integral, with proper rounding.
	   Use this when you know that x will be positive, as it has no
	   comparisons, and is thus more efficient. */
	template <std::integral Cast_to, std::floating_point Cast_from>
	constexpr Cast_to Unsigned(const Cast_from x) noexcept
	{
		return SC<Cast_to>(x + 0.5);
	}
}



/* Get the bigger of two numbers. */
template <lyo::Arithmetic Number>
constexpr Number Max(Number first, Number second) noexcept
{
	return first >= second ? first : second;
}

/* Get the smaller of two numbers. */
template <lyo::Arithmetic Number>
constexpr Number Min(Number first, Number second) noexcept
{
	return first <= second ? first : second;
}

/* Clamp a number in a range of <lower, upper>. */
template <lyo::Arithmetic Number>
constexpr Number Clamp(Number x, Number lower, Number upper) noexcept
{
	return (x >= upper) ? upper : ((x <= lower) ? lower : x);
}



/* Convert a 32-bit RGB hex value into an SDL_Color struct. */
constexpr SDL_Color HexToColor(lyo::u32 value) noexcept
{
	using Color = decltype(SDL_Color::r);

	return SDL_Color
	{
		SC<Color>((value >> 16) & 0xFF),
		SC<Color>((value >>	 8)	& 0xFF),
		SC<Color>( value		& 0xFF),
		255
	};
}
END_LYO_NAMESPACE