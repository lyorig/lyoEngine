#pragma once

#include "macros.h"

/* renderer.h:
   Wrapper class for SDL_Renderer. */

struct SDL_Renderer;
NAMESPACE_DECL(lyo, class Engine; class Window)

BEGIN_LYO_NAMESPACE
class Renderer
{
	static SDL_Renderer* Create(lyo::Window& window, unsigned flags) noexcept;

	SDL_Renderer* p_renderer;

public:

	Renderer(lyo::Window& window, unsigned flags) noexcept;
	DISABLE_COPY_CTORS(Renderer);

	~Renderer();

	void present()	SAFE;
	void clear()	SAFE;

	operator SDL_Renderer* () SAFE;
};
END_LYO_NAMESPACE