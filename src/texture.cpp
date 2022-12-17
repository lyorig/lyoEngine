#include <SDL_image.h>
#include "texture.h"
#include "window.h"
#include "engine.h"

SDL_Texture* lyo::Texture::Create(const lyo::Window& window, lyo::Size::Texture& size, lyo::cstring filename) noexcept
{
	SDL_Surface* temp_surface{ ::IMG_Load(filename) };
	if (temp_surface)
	{
		size.x = SC<lyo::SizeType::Texture>(temp_surface->w);
		size.y = SC<lyo::SizeType::Texture>(temp_surface->h);

		IF_DEBUG
			lyo::Engine::Log << "Created texture (" << size.x << ' ' << size.y << ")\n";

		SDL_Texture* texture{ ::SDL_CreateTextureFromSurface(window.renderer(), temp_surface) };
		if (!texture)
			Engine::Crash("SDL_CreateTextureFromSurface failed!");

		::SDL_FreeSurface(temp_surface);

		return texture;
	}
	else
	{
		Engine::Crash("IMG_Load failed!");
		return nullptr;
	}
}



lyo::Texture::Texture(const lyo::Window& window, lyo::cstring filename, double scale, SDL_BlendMode mode) noexcept :
	m_window	{ window },
	m_texture	{ Texture::Create(window, m_size, filename) },
	m_area		{ 0, 0, m_size.x, m_size.y },
	m_scale		{ scale },
	opacity		{ 255.0, SC<double>(SDL_ALPHA_TRANSPARENT), SC<double>(SDL_ALPHA_OPAQUE) }
{
	set_blend_mode(mode);
}

lyo::Texture::~Texture()
{
	::SDL_DestroyTexture(m_texture);
}



lyo::Texture& lyo::Texture::operator=(lyo::cstring filename) noexcept
{
	::SDL_DestroyTexture(m_texture);

	m_texture = Texture::Create(m_window, m_size, filename);
	m_area = { 0, 0, m_size.x, m_size.y };

	return *this;
}



void lyo::Texture::set_blend_mode(SDL_BlendMode mode) SAFE
{
	if (::SDL_SetTextureBlendMode(m_texture, mode) < 0)
		Engine::Crash("SDL_SetTextureBlendMode failed!");
}

void lyo::Texture::set_opacity(lyo::u8 value) SAFE
{
	if (::SDL_SetTextureAlphaMod(m_texture, value) < 0)
		Engine::Crash("SDL_SetTextureBlendMode failed!");
}



void lyo::Texture::set_area(const lyo::Area::Texture& area) noexcept
{
	m_area = area;
}

void lyo::Texture::set_scale(double value) noexcept
{
	m_scale = value;
}



void lyo::Texture::draw(const lyo::Coordinate& destination, double angle, SDL_RendererFlip flip) SAFE
{
	using namespace lyo::Type;

	const SDL_Rect src{ SC<SDL_Rect>(m_area) };

	COMPILE_IF(lyo::Settings::Float_Draw)
	{
		const SDL_FRect dst
		{
			SC<FRect>(destination.x),
			SC<FRect>(destination.y),
			SC<FRect>(m_size.x * m_scale),
			SC<FRect>(m_size.y * m_scale)
		};

		if (::SDL_RenderCopyExF(m_window.renderer(), m_texture, &src, &dst, angle, NULL, flip) == -1)
			Engine::Crash("SDL_RenderCopyExF failed!");
	}
	else
	{
		const SDL_Rect dst
		{
			lyo::Cast::Unsigned<Rect>(destination.x),
			lyo::Cast::Unsigned<Rect>(destination.y),
			lyo::Cast::Unsigned<Rect>(m_size.x * m_scale),
			lyo::Cast::Unsigned<Rect>(m_size.y * m_scale)
		};

		if (::SDL_RenderCopyEx(m_window.renderer(), m_texture, &src, &dst, angle, NULL, flip) < 0)
			Engine::Crash("SDL_RenderCopyEx failed!");
	}
}

void lyo::Texture::update() SAFE
{
	if (::SDL_SetTextureAlphaMod(m_texture, SC<Uint8>(opacity)) < 0)
		Engine::Crash("SDL_SetTextureAlphaMod failed!");
}



const lyo::SizeType::Texture lyo::Texture::width() SAFE
{
	return lyo::Cast::Unsigned<lyo::SizeType::Texture>(m_area.width * m_scale);
}

const lyo::SizeType::Texture lyo::Texture::height() SAFE
{
	return lyo::Cast::Unsigned<lyo::SizeType::Texture>(m_area.height * m_scale);
}



lyo::Texture::operator SDL_Texture* () SAFE
{
	return m_texture;
}