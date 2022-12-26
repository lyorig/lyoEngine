#include "font.h"
#include "engine.h"
#include "settings.h"


TTF_Font* lyo::Font::Create(lyo::c_string font_path, lyo::ST::Font size) noexcept
{
	TTF_Font* temp_font{ ::TTF_OpenFont(font_path, size) };

	IF_DEBUG
		if (!temp_font)
			Engine::Crash("TTF_OpenFont failed!");

	return temp_font;
}



lyo::Font::Font(lyo::c_string font_path, lyo::ST::Font size) noexcept :
	m_font{ Font::Create(font_path, size) },
	m_path{ font_path },
	m_size{ size }
{

}



void lyo::Font::operator=(lyo::c_string font_path) noexcept
{
	/* This comparison might be unnecessary, as lyo::Text already 
	   ensures the strings are different. */
	if (!std::strcmp(font_path, m_path))
	{
		m_path = font_path;
		m_font = Font::Create(font_path, m_size);
	}
}



void lyo::Font::set_size(lyo::ST::Font size) noexcept
{
	if (size != m_size)
	{
		m_size = size;
		m_font = Font::Create(m_path, size);
	}
}



lyo::ST::Font lyo::Font::size() SAFE
{
	return m_size;
}

const lyo::String& lyo::Font::path() SAFE
{
	return m_path;
}



lyo::Font::operator TTF_Font* () SAFE
{
	return m_font;
}