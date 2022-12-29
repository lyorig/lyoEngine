#pragma once

#include <SDL_render.h>
#include <SDL_blendmode.h>

#include "types.h"
#include "utility/slider.h"
#include "utility/capsule.h"

/* texture.h:
   Wrapper class for SDL_Texture. */

struct SDL_Texture;
NAMESPACE_DECL(lyo, class Window; class Surface)

BEGIN_LYO_NAMESPACE
class Texture
{
public:

	lyo::OpacitySlider opacity;

	Texture(const lyo::Window& window, const lyo::Surface& surface, double scale = 1.0, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE) noexcept;

	virtual void operator=(const lyo::Surface& surface) noexcept;
	
	virtual void update() SAFE;
	void draw(const lyo::Coordinate& destination) SAFE;

	lyo::ST::Texture	width()		SAFE;
	lyo::ST::Texture	height()	SAFE;
	double					scale()		SAFE;
	double					angle()		SAFE;
	SDL_RendererFlip		flip()		SAFE;

	/* Returns a coordinate such that using it with draw() will render
	   the texture in the center of the window. */
	lyo::Coordinate center() SAFE;

	operator SDL_Texture* () SAFE;

public: // For debug purposes - make this protected later!

	static SDL_Texture* Create(const lyo::Window& window, const Surface& surface) noexcept;

	/* This being const means that textures can't be reassigned to other windows... for now. */
	const lyo::Window& m_window;

	void set_area(const Area::Texture& area)	noexcept;
	void set_scale(double value)				noexcept;
	void set_angle(double value)				noexcept;
	void set_flip(SDL_RendererFlip flip)		noexcept;

	/* Returns the area of the texture that is currently being drawn. */
	const lyo::Area::Texture& area() SAFE;

	/* Returns the size of the entire texture, not just the current drawn area. */
	const lyo::Size::Texture& size() SAFE;

private:

	lyo::Capsule<SDL_Texture, ::SDL_DestroyTexture> m_texture; // 16b

	lyo::Area::Texture m_area; // 8b - 16b
	lyo::Size::Texture m_size; // 4b - 8b

	double m_scale; // 8b
	double m_angle; // 8b

	SDL_RendererFlip m_flip; // 4b
};
END_LYO_NAMESPACE

