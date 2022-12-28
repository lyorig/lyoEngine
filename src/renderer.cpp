#include <SDL_render.h>

#include "engine.h"
#include "window.h"
#include "renderer.h"
#include "settings.h"

SDL_Renderer* lyo::Renderer::Create(lyo::Window& window, unsigned flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) noexcept
{
	SDL_Renderer* temp_renderer{ ::SDL_CreateRenderer(window, -1, flags) };

	IF_DEBUG
		if (!temp_renderer)
			Engine::Crash("SDL_CreateRenderer failed!");

	return temp_renderer;
}



lyo::Renderer::Renderer(lyo::Window& window, unsigned flags) noexcept :
	m_renderer{ Renderer::Create(window, flags) }
{

}



void lyo::Renderer::present() SAFE
{
	::SDL_RenderPresent(m_renderer);
}

void lyo::Renderer::clear() SAFE
{
	const int result{ ::SDL_RenderClear(m_renderer) };

	IF_DEBUG
		if (result < 0)
			Engine::Crash("SDL_RenderClear failed!");
}



lyo::Renderer::operator SDL_Renderer* () SAFE
{
	return m_renderer;
}