#pragma once

#include "macros.h"

/* settings.h:
   Compilation settings using constexpr and/or macros.
   General good practice: only use #define when each branch requires
   different libraries (those can't be conditionally included with constexpr). */

#define LYOENGINE_VERSION "v0.3"

BEGIN_LYO_NAMESPACE
namespace Settings
{
	SETTING bool	Debug			{ true };	// Debug mode which enables additional logging among other things.
	SETTING bool	Float_Draw		{ true };	// Draw using SDL's RenderCopyExF instead of RenderCopyEx.
	SETTING double	Default_Scale	{ 2.0 };	// The scale multiplier for every lyo::Texture-based entity.
	SETTING double	Animation_TTU	{ 0.1 };	// The default animation update time of lyo::AnimatedTexture.

	SETTING lyo::Size::Window BWS{ 1920, 1080 }; // The Base Window Size for texture scaling on different resolutions.
}
END_LYO_NAMESPACE

/* Use fast integer types (e.g. uint_fast8_t instead of uint8_t).
   This is automatically defined in Optimized/Release mode! */
// #define USE_FAST_INTEGER_TYPES