
#include <SDL_image.h>

#include "surface.h"
#include "engine.h"

SDL_Surface* lyo::Surface::Create(lyo::c_string file_name) noexcept
{
	SDL_Surface* temp_surface{ ::IMG_Load(file_name) };

	IF_DEBUG
		if (!temp_surface)
			Engine::Crash("IMG_Load failed!");

	return temp_surface;
}



lyo::Surface::Surface(lyo::c_string file_name) noexcept :
	m_surface{ Surface::Create(file_name) }
{

}

lyo::Surface::Surface(SDL_Surface* surface) noexcept :
	m_surface{ surface }
{

}



lyo::ST::Texture lyo::Surface::width() SAFE
{
	return SC<lyo::ST::Texture>(m_surface->w);
}
lyo::ST::Texture lyo::Surface::height() SAFE
{
	return SC<lyo::ST::Texture>(m_surface->h);
}



lyo::Surface::operator SDL_Surface* () SAFE
{
	return m_surface;
}