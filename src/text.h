#pragma once

#include <SDL_ttf.h>
#include <string>

#include "font.h"
#include "texture.h"
#include "surface.h"

/* text.h:
   A texture containing text, rendered with SDL_ttf. */

BEGIN_LYO_NAMESPACE
class Text final : public Texture
{
public:

	Text(const lyo::Window& window, const Font& font, const lyo::String& text, lyo::u32 color = 0xFFFFFF, double scale = 1.0) noexcept;

	void set_font	(lyo::c_string font_path)	noexcept;
	void set_color	(lyo::u32 color)				noexcept;

	const lyo::String& content() SAFE;

	void operator=(lyo::c_string text) noexcept;

private:

	static lyo::Surface Create(const lyo::String& text, const Font& font, lyo::u32 color) noexcept;

	lyo::Font	m_font; // 40b
	lyo::String m_text; // 16b

	lyo::u32	m_color; // 4b
};
END_LYO_NAMESPACE