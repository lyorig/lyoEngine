#pragma once

#include "utility/macros.h"

/* renderer.h:
   Wrapper class for SDL_Renderer. */

struct SDL_Renderer;
NAMESPACE_DECL(lyo, class Engine)
NAMESPACE_DECL(lyo, class Window)

BEGIN_LYO_NAMESPACE
class Renderer
{
	static SDL_Renderer* Create(lyo::Window& window, unsigned flags);

	SDL_Renderer* p_renderer;

public:

	Renderer(lyo::Window& window, unsigned flags);
	~Renderer();

	void present() const;
	void clear() const;

	operator SDL_Renderer* () const;
};
END_LYO_NAMESPACE