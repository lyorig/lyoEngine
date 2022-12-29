#pragma once

#include "macros.h"
#include "utility/capsule.h"

/* renderer.h:
   Wrapper class for SDL_Renderer. */

struct SDL_Renderer;
NAMESPACE_DECL(lyo, class Engine; class Window)

BEGIN_LYO_NAMESPACE
class Renderer
{
public:

	Renderer(lyo::Window& window, unsigned flags) noexcept;

	void present()	SAFE;
	void clear()	SAFE;

	operator SDL_Renderer* () SAFE;

private:

	static SDL_Renderer* Create(lyo::Window& window, unsigned flags) noexcept;

	lyo::Capsule<SDL_Renderer, ::SDL_DestroyRenderer> m_renderer; // 16b
};
END_LYO_NAMESPACE