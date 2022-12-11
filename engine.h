#pragma once

#include <fstream>
#include <vector>
#include <SDL_error.h>
#include "utility/types.h"

/* engine.h:
   The "engine" itself, which is responsible for initializing
   (and deinitializing) all SDL facilities, on which it is built upon. Also
   includes various system info, such as displays etc.
   
   It consists of 2 parts: a constructor and destructor, responsible for 
   (de)initializing SDL, and static logging functions. */

struct SDL_Rect;

BEGIN_LYO_NAMESPACE
class Engine
{
	std::vector<SDL_Rect> v_displays;

public:

	Engine(unsigned init_flags);
	~Engine();

	static std::ofstream Log;
	static void Crash(lyo::cstring reason, lyo::cstring description = ::SDL_GetError());

	const std::vector<SDL_Rect>& displays() const;
};
END_LYO_NAMESPACE