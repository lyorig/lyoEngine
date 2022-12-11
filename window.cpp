#include <SDL_video.h>
#include "window.h"
#include "engine.h"
#include "globals.h"

SDL_Window* lyo::Window::Create(lyo::cstring name, const lyo::Point<int>& size, unsigned flags)
{
	SDL_Window* temp_window{ ::SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, flags) };

	if (!temp_window)
		Engine::Crash("SDL_CreateWindow failed!");

	return temp_window;
}

SDL_DisplayMode lyo::Window::GetDisplayInfo(int index)
{
	SDL_DisplayMode temp_dm;

	if (::SDL_GetDesktopDisplayMode(index, &temp_dm) < 0)
		Engine::Crash("SDL_GetDesktopDisplayMode failed!");

	return temp_dm;
}



lyo::Window::Window(lyo::cstring name, const lyo::Point<int>& size, unsigned flags) :
	p_window		{ Window::Create(name, size, flags) },
	m_monitorInfo	{ Window::GetDisplayInfo(0) },
	m_index			{ SC<decltype(m_index)>(::SDL_GetWindowDisplayIndex(p_window)) }
{
	IF_DEBUG
	{
		Engine::Log	<< "Creating monitor at index " << ::SDL_GetWindowDisplayIndex(p_window)
						<< ".\nMonitor resolution: " << m_monitorInfo.w << 'x' << m_monitorInfo.h
						<< "\nRefresh rate: " << m_monitorInfo.refresh_rate << '\n';
	}
}

lyo::Window::~Window()
{
	::SDL_DestroyWindow(p_window);
}



void lyo::Window::set_name(lyo::cstring name) const
{
	::SDL_SetWindowTitle(p_window, name);
}

lyo::u16 lyo::Window::hz()
{
	return SC<lyo::u16>(m_monitorInfo.refresh_rate);
}

lyo::u16 lyo::Window::width()
{
	return SC<lyo::u16>(m_monitorInfo.w);
}

lyo::u16 lyo::Window::height()
{
	return SC<lyo::u16>(m_monitorInfo.h);
}

lyo::u8 lyo::Window::index()
{
	return m_index;
}



lyo::Window::operator SDL_Window* () { return p_window; }