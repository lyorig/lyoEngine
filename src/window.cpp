#include <SDL_video.h>
#include <SDL_render.h>

#include "window.h"
#include "engine.h"

SDL_Window* lyo::Window::Create(lyo::c_string name, const lyo::Size::Window& size, unsigned flags) noexcept
{
	SDL_Window* temp_window{ ::SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, flags) };

	if (!temp_window)
		Engine::Crash("SDL_CreateWindow failed!");

	return temp_window;
}

SDL_DisplayMode lyo::Window::GetDisplayInfo(int index) noexcept
{
	SDL_DisplayMode temp_dm;

	const int result{ ::SDL_GetDesktopDisplayMode(index, &temp_dm) };

	IF_DEBUG
		if (result < 0)
			Engine::Crash("SDL_GetDesktopDisplayMode failed!");

	return temp_dm;
}



lyo::Window::Window(lyo::c_string name, lyo::Mixer& mixer, lyo::Input& input, const lyo::Size::Window& size, Uint32 window_flags, Uint32 renderer_flags) noexcept :
	m_window	{ Window::Create(name, size, window_flags) },
	m_info		{ Window::GetDisplayInfo(::SDL_GetWindowDisplayIndex(m_window)) },
	m_renderer	{ *this, renderer_flags },
	m_index		{ SC<decltype(m_index)>(::SDL_GetWindowDisplayIndex(m_window)) },
	mixer		{ mixer },
	input		{ input }
{
	IF_DEBUG
		if (m_index < 0)
				Engine::Crash("SDL_GetWindowDisplayIndex failed!");

	IF_DEBUG
	{
		Engine::Log	<< "Creating window on monitor #" << m_index + 1
					<< "\nMonitor resolution: " << m_info.w << 'x' << m_info.h
					<< "\nRefresh rate: " << m_info.refresh_rate << "hz\n" << std::endl;
	}
}



void lyo::Window::set_name(lyo::c_string name) SAFE
{
	::SDL_SetWindowTitle(m_window, name);
}

void lyo::Window::draw()
{
	m_renderer.present();
	m_renderer.clear();
}



const lyo::Renderer& lyo::Window::renderer() SAFE
{
	return m_renderer;
}



lyo::ST::Window lyo::Window::hz() SAFE
{
	return SC<lyo::ST::Window>(m_info.refresh_rate);
}

lyo::ST::Window lyo::Window::width() SAFE
{
	return SC<lyo::ST::Window>(m_info.w);
}

lyo::ST::Window lyo::Window::height() SAFE
{
	return SC<lyo::ST::Window>(m_info.h);
}

lyo::u8 lyo::Window::index() SAFE
{
	return m_index;
}



lyo::Window::operator SDL_Window*() SAFE
{
	return m_window;
}