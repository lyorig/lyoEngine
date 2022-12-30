#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "text.h"
#include "engine.h"

lyo::Surface lyo::Text::Create(const lyo::String& text, const Font& font, lyo::u32 color) noexcept
{
	/* We're essentially counting on the user inputting a string that is < 256 chars. Whoops. */
	const lyo::size buffer_size{ text.length() + 1 };

	wchar_t* convert{ new wchar_t[buffer_size] };

	const int result{ ::MultiByteToWideChar(CP_ACP, NULL, text, -1, convert, SC<int>(buffer_size)) };

	IF_DEBUG
	{
		if (!result)
		{
			lyo::String error;

			switch (::GetLastError())
			{
			case ERROR_INSUFFICIENT_BUFFER:
				error = "Insufficient (or NULL) buffer size.";
				break;

			case ERROR_INVALID_FLAGS:
				error = "Invalid flags.";
				break;

			case ERROR_INVALID_PARAMETER:
				error = "Invalid parameters.";
				break;

			case ERROR_NO_UNICODE_TRANSLATION:
				error = "The string contains invalid Unicode.";
				break;

			default:
				error = "Unknown error. This shouldn't happen!";
				break;
			}

			Engine::Crash("MultiByteToWideChar failed!", error);
		}
	}
		
	SDL_Surface* temp_surface{ ::TTF_RenderUNICODE_LCD_Wrapped(font, RC<const Uint16*>(convert), lyo::HexToColor(color), {0, 0, 0, 0}, NULL)};

	delete[] convert;

	IF_DEBUG
		if (!temp_surface)
			Engine::Crash("TTF_RenderUTF8_LCD_Wrapped failed!");

	return temp_surface;
}



lyo::Text::Text(const lyo::Window& window, const Font& font, const lyo::String& text, lyo::u32 color, double scale) noexcept :
	Texture	{ window, Text::Create(text, font, color), scale },
	m_font	{ font },
	m_text	{ text },
	m_color	{ color }
{

}



void lyo::Text::set_font(const lyo::String& font_path) noexcept
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



const lyo::String& lyo::Text::content() SAFE
{
	return m_text;
}



void lyo::Text::operator=(const lyo::String& text) noexcept
{
	m_text = text;
	Texture::operator=(Text::Create(text, m_font, m_color));
}