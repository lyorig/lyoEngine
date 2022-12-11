#include <SDL_image.h>
#include "texture.h"
#include "renderer.h"
#include "engine.h"

SDL_Texture* lyo::Texture::Create(const lyo::Renderer& renderer, lyo::cstring filename)
{
	SDL_Surface* temp_surface{ ::IMG_Load(filename) };
	if (!temp_surface)
		Engine::Crash("IMG_Load failed!");

	SDL_Texture* temp_texture{ ::SDL_CreateTextureFromSurface(renderer, temp_surface) };
	if (!temp_texture)
		Engine::Crash("SDL_CreateTextureFromSurface failed!");

	::SDL_FreeSurface(temp_surface);

	return temp_texture;
}



lyo::Texture::Texture(const lyo::Renderer& renderer, lyo::cstring filename, SDL_BlendMode mode) :
	m_renderer	{ renderer },
	m_texture	{ Texture::Create(renderer, filename) }
{
	/* reinterpret_cast is evil, but so am I! */
	if (::SDL_QueryTexture(m_texture, NULL, NULL, RC<int*>(&m_size.x), RC<int*>(&m_size.y)) < 0)
		Engine::Crash("SDL_QueryTexture failed!");

	this->set_blend_mode(mode);
}

lyo::Texture::~Texture()
{
	::SDL_DestroyTexture(m_texture);
}



void lyo::Texture::set_blend_mode(SDL_BlendMode mode) const
{
	if (::SDL_SetTextureBlendMode(m_texture, mode) < 0)
		Engine::Crash("SDL_SetTextureBlendMode failed!");
}

void lyo::Texture::draw(const lyo::Area::Texture& src_rect, const lyo::Coordinate& dst_rect, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE) const
{
	const SDL_Rect src{ SC<SDL_Rect>(src_rect) };

	COMPILE_IF (lyo::Settings::Float_Draw)
	{
		const SDL_FRect dst{ SC<SDL_FRect>(src_rect) };

		if (::SDL_RenderCopyExF(m_renderer, m_texture, &src, &dst, angle, NULL, flip) == -1)
			Engine::Crash("SDL_RenderCopyExF failed!");
	}
	else
	{
		const SDL_Rect dst{ SC<SDL_Rect>(src_rect) };

		if (::SDL_RenderCopyEx(m_renderer, m_texture, &src, &dst, angle, NULL, flip) == -1)
			Engine::Crash("SDL_RenderCopyEx failed!");
	}
}



lyo::Area::Texture lyo::Texture::area() const
{
	return lyo::Area::Texture
	{
		0,
		0,
		SC<decltype(lyo::Area::Texture::x)>(m_size.x),
		SC<decltype(lyo::Area::Texture::x)>(m_size.y)
	};
}

lyo::u16 lyo::Texture::width() const
{
	return m_size.x;
}

lyo::u16 lyo::Texture::height() const
{
	return m_size.y;
}



lyo::Texture::operator SDL_Texture* () const
{
	return m_texture;
}