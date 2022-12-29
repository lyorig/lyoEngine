#include <SDL_image.h>
#include <SDL_ttf.h>

#include "window.h"
#include "engine.h"
#include "texture.h"
#include "surface.h"

SDL_Texture* lyo::Texture::Create(const lyo::Window& window, const Surface& surface) noexcept
{
	SDL_Texture* temp_texture{ ::SDL_CreateTextureFromSurface(window.renderer(), surface) };

	IF_DEBUG
		if (!temp_texture)
			Engine::Crash("SDL_CreateTextureFromSurface failed!");

	return temp_texture;
}



lyo::Texture::Texture(const lyo::Window& window, const lyo::Surface& surface, double scale, double angle, SDL_RendererFlip flip) noexcept :
	m_window	{ window },
	m_texture	{ Texture::Create(window, surface) },
	m_area		{ 0, 0, surface.width(), surface.height() },
	m_size		{ m_area.width, m_area.height },
	m_scale		{ scale * (window.height() / SC<double>(lyo::Settings::BWS.y)) },
	m_angle		{ angle },
	m_flip		{ flip },
	opacity		{ 255.0 }
{
	const int result{ ::SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND) };

	IF_DEBUG
		if (result < 0)
			Engine::Crash("SDL_SetTextureBlendMode failed!");
}



void lyo::Texture::operator=(const lyo::Surface& surface) noexcept
{
	m_texture = Texture::Create(m_window, surface);

	m_size = { surface.width(), surface.height() };
	m_area = { 0, 0, m_size.x, m_size.y };
}



const lyo::Area::Texture& lyo::Texture::area() SAFE
{
	return m_area;
}

const lyo::Size::Texture& lyo::Texture::size() SAFE
{
	return m_size;
}



void lyo::Texture::set_area(const lyo::Area::Texture& area) noexcept
{
	m_area = area;
}

void lyo::Texture::set_scale(double value) noexcept
{
	m_scale = value * (m_window.height() / SC<double>(lyo::Settings::BWS.y));
}

void lyo::Texture::set_angle(double value) noexcept
{
	m_angle = value;
}

void lyo::Texture::set_flip(SDL_RendererFlip flip) noexcept
{
	m_flip = flip;
}



void lyo::Texture::draw(const lyo::Coordinate& destination) SAFE
{
	using namespace lyo::Type;

	const SDL_Rect src{ SC<SDL_Rect>(m_area) };

	COMPILE_IF (lyo::Settings::Float_Draw)
	{
		const SDL_FRect dst
		{
			SC<FRect>(destination.x),
			SC<FRect>(destination.y),
			SC<FRect>(m_area.width * m_scale),
			SC<FRect>(m_area.height * m_scale)
		};

		const int result{ ::SDL_RenderCopyExF(m_window.renderer(), m_texture, &src, &dst, m_angle, NULL, m_flip) };

		IF_DEBUG
			if (result == -1)
				Engine::Crash("SDL_RenderCopyExF failed!");
	}
	else
	{
		const SDL_Rect dst
		{
			lyo::Cast::Unsigned<Rect>(destination.x),
			lyo::Cast::Unsigned<Rect>(destination.y),
			lyo::Cast::Unsigned<Rect>(m_area.width * m_scale),
			lyo::Cast::Unsigned<Rect>(m_area.height * m_scale)
		};

		const int result{ ::SDL_RenderCopyEx(m_window.renderer(), m_texture, &src, &dst, m_angle, NULL, m_flip) };

		IF_DEBUG
			if (result == -1)
				Engine::Crash("SDL_RenderCopyEx failed!");
	}
}

void lyo::Texture::update() SAFE
{
	const int result{ ::SDL_SetTextureAlphaMod(m_texture, SC<Uint8>(opacity)) };

	IF_DEBUG
		if (result < 0)
			Engine::Crash("SDL_SetTextureAlphaMod failed!");
}



lyo::ST::Texture lyo::Texture::width() SAFE
{
	return lyo::Cast::Unsigned<lyo::ST::Texture>(m_area.width * m_scale);
}

lyo::ST::Texture lyo::Texture::height() SAFE
{
	return lyo::Cast::Unsigned<lyo::ST::Texture>(m_area.height * m_scale);
}

double lyo::Texture::scale() SAFE
{
	return m_scale;
}

double lyo::Texture::angle() SAFE
{
	return m_angle;
}

SDL_RendererFlip lyo::Texture::flip() SAFE
{
	return m_flip;
}



lyo::Coordinate lyo::Texture::center() SAFE
{
	return lyo::Coordinate
	{
		m_window.width() / 2.0 - this->width() / 2.0,
		m_window.height() / 2.0 - this->height() / 2.0
	};
}



lyo::Texture::operator SDL_Texture* () SAFE
{
	return m_texture;
}