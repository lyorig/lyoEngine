#pragma once

#include <SDL_ttf.h>

#include "utility/string.h"
#include "utility/capsule.h"

#define FONT(file) "assets/fonts/" ## file

/* font.h:
   Wrapper class for TTF_Font. */

BEGIN_LYO_NAMESPACE
class Font
{
public:

	Font(const lyo::String& font_path, lyo::ST::Font size) noexcept;

	void operator=(const lyo::String& font_path) noexcept;

	void set_size(lyo::ST::Font size) noexcept;

	lyo::ST::Font		size() SAFE;
	const lyo::String&	path() SAFE;

	operator TTF_Font* () SAFE;

private:

	static TTF_Font* Create(const lyo::String& font_path, lyo::ST::Font size) noexcept;

	lyo::Capsule<TTF_Font, ::TTF_CloseFont> m_font; // 16b

	lyo::String m_path; // 16b

	lyo::ST::Font m_size; // 2b - 4b
};
END_LYO_NAMESPACE