#include "text.h"
#include "engine.h"

lyo::Surface lyo::Text::Create(lyo::c_string text, const Font& font, lyo::u32 color) noexcept
{
	SDL_Surface* temp_surface{ ::TTF_RenderUTF8_LCD_Wrapped(font, text, lyo::HexToColor(color), {0, 0, 0, 0}, NULL) };
	IF_DEBUG
		if (!temp_surface)
			Engine::Crash("TTF_RenderUTF8_LCD_Wrapped failed!");

	return temp_surface;
}



lyo::Text::Text(lyo::Window& window, const Font& font, lyo::c_string text, lyo::u32 color, double scale) noexcept :
	Texture	{ window, Text::Create(text, font, color), scale },
	m_font	{ font },
	m_text	{ text },
	m_color	{ color }
{

}



void lyo::Text::set_font(lyo::c_string font_path) noexcept
{
	if (!std::strcmp(font_path, m_font.path()))
	{
		m_font = font_path;
		Texture::operator=(Text::Create(m_text, m_font, m_color));
	}
}

void lyo::Text::set_color(lyo::u32 color) noexcept
{
	if (color != m_color)
	{
		m_color = color;
		Texture::operator=(Text::Create(m_text, m_font, color));
	}
}



lyo::c_string lyo::Text::content() SAFE
{
	return m_text;
}



void lyo::Text::operator=(lyo::c_string text) noexcept
{
	m_text = text;
	Texture::operator=(Text::Create(text, m_font, m_color));
}