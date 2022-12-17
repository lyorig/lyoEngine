#pragma once

#include <SDL_blendmode.h>
#include <SDL_render.h>
#include "types.h"
#include "utility/slider.h"

/* texture.h:
   Wrapper class for SDL_Texture. */

struct SDL_Texture;
NAMESPACE_DECL(lyo, class Window)

BEGIN_LYO_NAMESPACE
class Texture
{
public: // For debug purposes - make these protected later!

	const lyo::Window& m_window;

	void set_area(const lyo::Area::Texture& area) noexcept;
	void set_scale(double value) noexcept;
	void set_blend_mode(SDL_BlendMode mode) SAFE;
	void set_opacity(lyo::u8 value)			SAFE;
	

private:

	static SDL_Texture* Create(const lyo::Window& window, lyo::Size::Texture& size, lyo::cstring filename) noexcept;

	/* About the weird placement here. We can avoid having to use SDL_QueryTexture()
	   by getting the size info from the surface while creating it. This is written
	   to the "size" parameter in Texture::Create(). However, we must initialize it
	   before the texture, or it'll get overwritten. */

	lyo::Size::Texture m_size;

	SDL_Texture* m_texture;

	lyo::Area::Texture m_area;

	double m_scale;

public:

	lyo::Slider<double> opacity;

	Texture(const lyo::Window& window, lyo::cstring filename, double scale = 1.0, SDL_BlendMode mode = SDL_BLENDMODE_BLEND) noexcept;
	DISABLE_COPY_CTORS(Texture);

	~Texture();

	Texture& operator=(lyo::cstring filename) noexcept;
	
	virtual void update() SAFE;
	void draw(const lyo::Coordinate& destination, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE) SAFE;

	const lyo::SizeType::Texture	width()		SAFE;
	const lyo::SizeType::Texture	height()	SAFE;

	operator SDL_Texture* () SAFE;
};
END_LYO_NAMESPACE

