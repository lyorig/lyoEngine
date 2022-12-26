#pragma once

#include <SDL_surface.h>

#include "types.h"
#include "utility/string.h"
#include "utility/capsule.h"

BEGIN_LYO_NAMESPACE
class Surface
{
	static SDL_Surface* Create(lyo::c_string file_name) noexcept;

	lyo::Capsule<SDL_Surface, ::SDL_FreeSurface> m_surface; // 16b

public:

	Surface(lyo::c_string file_name) noexcept;
	Surface(SDL_Surface* surface) noexcept;

	lyo::ST::Texture width() SAFE;
	lyo::ST::Texture height() SAFE;

	operator SDL_Surface* () SAFE;
};
END_LYO_NAMESPACE