#pragma once

#include <SDL_render.h>
#include "macros.h"

/* settings.h:
   Compilation settings using constexpr and/or macros.
   General good practice: only use #define when each branch requires
   different libraries (which can't be conditionally included with constexpr). */

#define LYOENGINE_VERSION "v0.3"

BEGIN_LYO_NAMESPACE
namespace Settings
{
	SETTING bool	Debug			{ true };	// Debug mode which enables additional logging among other things.
	SETTING bool	Float_Draw		{ true };	// Draw using SDL's RenderCopyExF instead of RenderCopyEx.
	SETTING double	Default_Scale	{ 2.0 };	// The scale multiplier for every lyo::Texture-based entity.
	SETTING double	Animation_TTU	{ 0.1 };	// The default animation update time of lyo::AnimatedTexture.

	SETTING lyo::u32 Window_Flags	{ SDL_WINDOW_FULLSCREEN_DESKTOP };							// Default window flags.
	SETTING lyo::u32 Renderer_flags	{ SDL_RENDERER_ACCELERATED };	// Default renderer flags for a window.

	SETTING lyo::ST::Music	Music_Volume	{ 80 };		// The default volume for music.
	SETTING lyo::ST::Music	Chunk_Volume	{ 80 };		// The default volume for SFX.
	SETTING double			Music_Fade_Time	{ 4.0 };	// The time (in seconds) it takes for music to fade in/out.
	SETTING lyo::u16		Music_Frequency	{ 48000 };	// The sampling rate of music.

	SETTING lyo::Size::Window BWS{ 1920, 1080 }; // The Base Window Size for texture scaling on different resolutions.
}
END_LYO_NAMESPACE

/* Use fast integer types (e.g. uint_fast8_t instead of uint8_t).
   This is automatically defined in Optimized/Release mode! */
// #define USE_FAST_INTEGER_TYPES