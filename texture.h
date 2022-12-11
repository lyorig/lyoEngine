#pragma once

#include "utility/types.h"

/* texture.h:
   Wrapper class for SDL_Texture. */

struct SDL_Texture;
NAMESPACE_DECL(lyo, class Renderer)

BEGIN_LYO_NAMESPACE
class Texture
{
	static SDL_Texture* Create(const lyo::Renderer& renderer, lyo::cstring filename);

	lyo::Size::Sprite m_size;

	const lyo::Renderer& m_renderer;
	SDL_Texture* m_texture;

public:

	Texture(const lyo::Renderer& renderer, lyo::cstring filename, SDL_BlendMode mode);
	~Texture();

	void set_blend_mode(SDL_BlendMode mode) const;
	void draw(const lyo::Area::Texture& src_rect, const lyo::Coordinate& dst_rect, double angle, SDL_RendererFlip flip) const;

	lyo::Area::Texture area() const;
	lyo::u16 width() const;
	lyo::u16 height() const;

	operator SDL_Texture* () const;
};
END_LYO_NAMESPACE

