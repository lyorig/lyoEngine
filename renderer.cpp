#include <SDL_render.h>
#include "renderer.h"
#include "globals.h"
#include "engine.h"
#include "window.h"

SDL_Renderer* lyo::Renderer::Create(lyo::Window& window, unsigned flags)
{
	SDL_Renderer* temp_renderer{ ::SDL_CreateRenderer(window, -1, flags) };

	if (!temp_renderer)
		Engine::Crash("SDL_CreateRenderer failed!");

	return temp_renderer;
}



lyo::Renderer::Renderer(lyo::Window& window, unsigned flags) :
	p_renderer{ Renderer::Create(window, flags) }
{

}

lyo::Renderer::~Renderer()
{
	::SDL_DestroyRenderer(p_renderer);
}



void lyo::Renderer::present() const
{
	::SDL_RenderPresent(p_renderer);
}

void lyo::Renderer::clear() const
{
	if (::SDL_RenderClear(p_renderer) < 0)
		Engine::Crash("SDL_RenderClear failed!");
}



lyo::Renderer::operator SDL_Renderer* () const { return p_renderer; }