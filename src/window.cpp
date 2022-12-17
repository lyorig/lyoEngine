#include <SDL_video.h>
#include <SDL_render.h>
#include "window.h"
#include "engine.h"

SDL_Window* lyo::Window::Create(lyo::cstring name, const lyo::Size::Window& size, unsigned flags) noexcept
{
	SDL_Window* temp_window{ ::SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, flags) };

	if (!temp_window)
		Engine::Crash("SDL_CreateWindow failed!");

	return temp_window;
}

SDL_DisplayMode lyo::Window::GetDisplayInfo(int index) noexcept
{
	SDL_DisplayMode temp_dm;

	if (::SDL_GetDesktopDisplayMode(index, &temp_dm) < 0)
		Engine::Crash("SDL_GetDesktopDisplayMode failed!");

	return temp_dm;
}



lyo::Window::Window(lyo::cstring name, lyo::Mixer& mixer, lyo::Input& input, const lyo::Size::Window& size, unsigned window_flags, unsigned renderer_flags) noexcept :
	m_window	{ Window::Create(name, size, window_flags) },
	m_info		{ Window::GetDisplayInfo(0) },
	m_renderer	{ *this, renderer_flags },
	m_index		{ SC<decltype(m_index)>(::SDL_GetWindowDisplayIndex(m_window)) },
	mixer		{ mixer },
	input		{ input }
{
	IF_DEBUG
	{
		const int idx{ ::SDL_GetWindowDisplayIndex(m_window) };
		if (idx < 0)
			Engine::Crash("SDL_GetWindowDisplayIndex failed!");

		Engine::Log	<< "Creating window on monitor #" << idx
					<< "\nMonitor resolution: " << m_info.w << 'x' << m_info.h
					<< "\nRefresh rate: " << m_info.refresh_rate << "hz\n";
	}
}

lyo::Window::~Window()
{
	::SDL_DestroyWindow(m_window);
}



void lyo::Window::set_name(lyo::cstring name) SAFE
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



lyo::SizeType::Window lyo::Window::hz() SAFE
{
	return SC<lyo::SizeType::Window>(m_info.refresh_rate);
}

lyo::SizeType::Window lyo::Window::width() SAFE
{
	return SC<lyo::SizeType::Window>(m_info.w);
}

lyo::SizeType::Window lyo::Window::height() SAFE
{
	return SC<lyo::SizeType::Window>(m_info.h);
}

lyo::u8 lyo::Window::index() SAFE
{
	return m_index;
}



lyo::Window::operator SDL_Window*() SAFE
{
	return m_window;
}