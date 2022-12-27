#pragma once

#include <SDL_ttf.h>

#include "utility/string.h"
#include "utility/capsule.h"

#define FONT(file) "assets/fonts/" ## file

BEGIN_LYO_NAMESPACE
class Font
{
	static TTF_Font* Create(lyo::c_string font_path, lyo::ST::Font size) noexcept;

	lyo::Capsule<TTF_Font, ::TTF_CloseFont> m_font; // 16b

	lyo::String m_path; // 16b

	lyo::ST::Font m_size; // 2b - 4b
public:

	Font(lyo::c_string font_path, lyo::ST::Font size) noexcept;

	void operator=(lyo::c_string font_path) noexcept;

	void set_size(lyo::ST::Font size) noexcept;

	lyo::ST::Font		size() SAFE;
	const lyo::String&	path() SAFE;

	operator TTF_Font* () SAFE;
};
END_LYO_NAMESPACE