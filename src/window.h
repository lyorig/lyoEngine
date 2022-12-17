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
	SDL_Window*		m_window;
	SDL_DisplayMode m_info;

	lyo::Renderer m_renderer; // Renderers can't be created without a window.

	lyo::u8 m_index;

	static SDL_Window* Create(lyo::cstring name, const lyo::Size::Window& size, unsigned flags) noexcept;
	static SDL_DisplayMode GetDisplayInfo(int index) noexcept;
	
public:

	/* Public subsystem references for ease of access. */
	lyo::Mixer& mixer;
	lyo::Input& input;

	Window(lyo::cstring name, lyo::Mixer& mixer, lyo::Input& input, const lyo::Size::Window& size = { 1920, 1080 }, unsigned window_flags = SDL_WINDOW_FULLSCREEN_DESKTOP, unsigned renderer_flags = SDL_RENDERER_ACCELERATED) noexcept;
	DISABLE_COPY_CTORS(Window);

	~Window();

	void set_name(lyo::cstring name) SAFE;
	void draw();

	const lyo::Renderer& renderer() SAFE;

	lyo::SizeType::Window hz()		SAFE;
	lyo::SizeType::Window width()	SAFE;
	lyo::SizeType::Window height()	SAFE;
	lyo::u8				  index()	SAFE;

	operator SDL_Window* () SAFE;
};
END_LYO_NAMESPACE