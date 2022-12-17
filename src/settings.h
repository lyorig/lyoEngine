#pragma once

#include "macros.h"

/* settings.h:
   Compilation settings using constexpr and/or macros.
   General good practice: only use #define when each branch requires
   different libraries (those can't be conditionally included with constexpr). */

#define LYOENGINE_VERSION "1.1"

BEGIN_LYO_NAMESPACE
namespace Settings
{
	SETTING Debug		{ true };	// Debug mode which enables additional logging among other things.
	SETTING Float_Draw	{ true };	// Draw using SDL's RenderCopyExF instead of RenderCopyEx.
}
END_LYO_NAMESPACE

/* Use fast integer types (e.g. uint_fast8_t instead of uint8_t).
   This is automatically defined in Optimized/Release mode! */
// #define USE_FAST_INTEGER_TYPES