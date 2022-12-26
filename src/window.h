#pragma once

#include "types.h"
#include "renderer.h"

/* window.h:
   Wrapper class for SDL_Window. */

struct SDL_Window;
NAMESPACE_DECL(lyo, class Mixer; class Input)

BEGIN_LYO_NAMESPACE
class Window
{
	lyo::Capsule<SDL_Window, ::SDL_DestroyWindow> m_window;	// 16b

	lyo::Renderer	m_renderer; // 16b
	lyo::u8			m_index;	// 1b

	SDL_DisplayMode	m_info; // 24b

	static SDL_Window*		Create(lyo::c_string name, const lyo::Size::Window& size, unsigned flags) noexcept;
	static SDL_DisplayMode	GetDisplayInfo(int index) noexcept;
	
public:

	/* Public subsystem references for ease of access. */
	lyo::Mixer& mixer;
	lyo::Input& input;

	Window(lyo::c_string name, lyo::Mixer& mixer, lyo::Input& input, const lyo::Size::Window& size = { 1920, 1080 }, Uint32 window_flags = SDL_WINDOW_FULLSCREEN_DESKTOP, Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) noexcept;

	void set_name(lyo::c_string name) SAFE;
	void draw();

	const lyo::Renderer& renderer() SAFE;

	lyo::ST::Window hz()		SAFE;
	lyo::ST::Window width()	SAFE;
	lyo::ST::Window height()	SAFE;
	lyo::u8				  index()	SAFE;

	operator SDL_Window* () SAFE;
};
END_LYO_NAMESPACE