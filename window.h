#pragma once

#include "utility/types.h"

/* window.h:
   Wrapper class for SDL_Window. */

struct SDL_Window;
NAMESPACE_DECL(lyo, class Engine)

BEGIN_LYO_NAMESPACE
class Window
{
	SDL_Window*		p_window;
	SDL_DisplayMode m_monitorInfo;

	lyo::u8 m_index;

	static SDL_Window* Create(lyo::cstring name, const lyo::Point<int>& size, unsigned flags);
	static SDL_DisplayMode GetDisplayInfo(int index);
	
public:

	Window(lyo::cstring name, const lyo::Point<int>& size, unsigned flags);
	~Window();

	void set_name(lyo::cstring name) const;

	/* Helper functions */
	lyo::u16 hz();
	lyo::u16 width();
	lyo::u16 height();
	lyo::u8 index();

	operator SDL_Window* ();
};
END_LYO_NAMESPACE