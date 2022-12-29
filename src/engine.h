#pragma once

#include <fstream>
#include <vector>
#include <SDL_error.h>

#include "types.h"
#include "settings.h"

/* engine.h:
   The "engine" itself, which is responsible for initializing
   (and deinitializing) all SDL facilities, on which it is built upon. Also
   includes various system info, such as displays etc.
   It consists of 2 parts: a constructor and destructor, responsible for 
   (de)initializing SDL, and static logging/crash functions. */

struct SDL_Rect;

BEGIN_LYO_NAMESPACE
class Engine
{
public:

	using DisplayVector = std::vector<lyo::Area::Window>;

	static std::ofstream Log;

	static void Warn	(lyo::c_string reason) noexcept;
	static void Crash	(lyo::c_string reason, lyo::c_string description = ::SDL_GetError()) noexcept;

	Engine(Uint32 init_flags) noexcept;
	DELETE_COPY_CTORS(Engine);

	~Engine();

	const DisplayVector& displays() SAFE;

private:

	DisplayVector m_displays;
};
END_LYO_NAMESPACE