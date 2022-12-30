#pragma once

#include <cstdint>
#include <ostream>
#include <SDL_rect.h>

#include "macros.h"

#include "utility/concepts.h"

/* types.h:
   Convenience typedefs for less verbose code, as well as
   globally used types for unified code. */

BEGIN_LYO_NAMESPACE
#ifdef USE_FAST_INTEGER_TYPES
using i8  =	std::int_fast8_t;	// -128 to 128
using i16 = std::int_fast16_t;	// -2,147,483,648 to 2,147,483,647
using i32 = std::int_fast32_t;	// -2,147,483,648 to 2,147,483,647
using i64 = std::int_fast64_t;	// -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 

using u8  =	std::uint_fast8_t;	// 0 to 255
using u16 = std::uint_fast16_t;	// 0 to 4,294,967,295
using u32 = std::uint_fast32_t;	// 0 to 4,294,967,295
using u64 = std::uint_fast64_t;	// 0 to 18,446,744,073,709,551,615
#else
using i8  =	std::int8_t;	// -128 to 128
using i16 = std::int16_t;	// -32,768 to 32,767
using i32 = std::int32_t;	// -2,147,483,648 to 2,147,483,647
using i64 = std::int64_t;	// -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807

using u8  =	std::uint8_t;	// 0 to 255
using u16 = std::uint16_t;	// 0 to 65,535
using u32 = std::uint32_t;	// 0 to 4,294,967,295
using u64 = std::uint64_t;	// 0 to 18,446,744,073,709,551,615
#endif

using size = std::size_t;

using c_string = const char*;
using w_string = const wchar_t*;



template <lyo::Arithmetic Number>
struct Point
{
	Number x{}, y{};

	constexpr bool operator==(const Point& other) SAFE
	{
		return x == other.x && y == other.y;
	}

	constexpr operator SDL_Rect() SAFE
	{
		return SDL_Rect
		{
			0,
			0,
			SC<int>(x),
			SC<int>(y),
		};
	}

	constexpr operator SDL_FRect() SAFE
	{
		return SDL_FRect
		{
			0.0F,
			0.0F,
			SC<float>(x),
			SC<float>(y)
		};
	}

	friend std::ostream& operator<<(std::ostream& str, const Point<Number>& pt) noexcept
	{
		str << '{' << pt.x << ", " << pt.y << '}';

		return str;
	}
};

template <lyo::Arithmetic Number>
struct Rectangle
{
	Number x{}, y{}, width{}, height{};

	// Overloaded comparison operator to test for overlaps.
	constexpr bool operator|(const Rectangle& other) SAFE
	{
		return (x < other.x + other.width	&&
				x + width > other.x			&&
				y < other.y + other.height	&&
				y + height > other.y);
	}

	constexpr operator SDL_Rect() SAFE
	{
		return SDL_Rect
		{
			SC<int>(x),
			SC<int>(y),
			SC<int>(width),
			SC<int>(height)
		};
	}

	constexpr operator SDL_FRect() SAFE
	{
		return SDL_FRect
		{
			SC<float>(x),
			SC<float>(y),
			SC<float>(width),
			SC<float>(height)
		};
	}

	template <lyo::Arithmetic Point_type>
	constexpr lyo::Point<Point_type> pos_point() SAFE
	{
		return lyo::Point<Point_type>
		{
			SC<Point_type>(x),
			SC<Point_type>(y)
		};
	}

	template <lyo::Arithmetic Point_type>
	constexpr lyo::Point<Point_type> size_point() SAFE
	{
		return lyo::Point<Point_type>
		{
			SC<Point_type>(width),
			SC<Point_type>(height)
		};
	}

	friend std::ostream& operator<<(std::ostream& str, const Rectangle<Number>& rect) noexcept
	{
		str << '{' << rect.x << ", " << rect.y << ", " << rect.width << ", " << rect.height << '}';

		return str;
	}
};



using Coordinate = lyo::Point<double>;

namespace Type
{
	using Rect	= decltype(SDL_Rect::x);
	using FRect = decltype(SDL_FRect::x);
}

/* Size types of various objects. */
namespace ST
{
	using Animation = lyo::u8;
	using Music		= lyo::u8;

	using Texture	= lyo::u16;
	using Window	= lyo::u16;
	using Font		= lyo::u16;

	using Level		= double;
}

/* Dimensions of various objects, implemented with lyo::Point. */
namespace Size
{
	using Animation = lyo::Point<lyo::ST::Animation>;	// The size of an animation, in frames.
	using Texture	= lyo::Point<lyo::ST::Texture>;		// The dimensions of a texture.
	using Window	= lyo::Point<lyo::ST::Window>;		// The dimensions of a window.
	using Level		= lyo::Point<lyo::ST::Level>;		// The dimensions of a level.
}

/* Areas of various objects, implemented with lyo::Rectangle. */
namespace Area
{
	using Texture	= lyo::Rectangle<lyo::ST::Texture>;	// An area of a texture.
	using Window	= lyo::Rectangle<lyo::ST::Window>;	// An area of a window.
	using World		= lyo::Rectangle<lyo::ST::Level>;	// An area in the game world.
}

template <typename Return_type, typename... Args>
using Function = Return_type(*)(Args...);
END_LYO_NAMESPACE