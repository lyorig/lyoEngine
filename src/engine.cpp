#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "engine.h"
#include "globals.h"

std::ofstream lyo::Engine::Log{ "lyoEngine output.txt" };

void lyo::Engine::Crash(lyo::cstring title, lyo::cstring description) noexcept
{
	/* We don't want to display an empty string as the description. */
	lyo::cstring err{ std::strlen(description) ? description : "(none)" };

	Engine::Log	<< "[CRASH] lyoEngine crashed!\nReason: " << title
					<< "\nError: " << err << "\nRuntime: " << g::runtime << '\n';

	const SDL_MessageBoxButtonData buttons[2]{ { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Exit" },
											   { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Run anyway" } };

	const SDL_MessageBoxData msgbox{ SDL_MESSAGEBOX_ERROR, NULL, title, err, 2, buttons, NULL };

	int response{ 0 };

	if (::SDL_ShowMessageBox(&msgbox, &response) < 0)
		Engine::Log << "[CRASH HANDLER] SDL_ShowMessageBox failed. The engine will preventively crash.\n";

	/* Assume the response hasn't changed if the message box failed to create. */
	if (!response)
		std::exit(EXIT_FAILURE);
}



lyo::Engine::Engine(unsigned init_flags) noexcept
{
	/* Initialize all SDL facilities. */
	if (::SDL_Init(init_flags) < 0)
		Engine::Crash("SDL_Init failed!");

	if (!::IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
		Engine::Crash("IMG_Init failed!");

	if (::TTF_Init() == -1)
		Engine::Crash("TTF_Init failed!");

	if (!::Mix_Init(MIX_INIT_MP3))
		Engine::Crash("Mix_Init failed!");

	/* Enumerate all displays and their dimensions. */
	const int displays{ ::SDL_GetNumVideoDisplays() };
	if (displays < 0)
		Engine::Crash("SDL_GetNumVideoDisplays failed!");

	m_displays.resize(SC<lyo::size>(displays));

	for (int i{ 0 }; i < displays; ++i)
	{
		SDL_Rect d;

		if (::SDL_GetDisplayBounds(i, &d) < 0)
			Engine::Crash("SDL_GetDisplayBounds failed!");

		m_displays[i] =
		{
			SC<lyo::SizeType::Window>(d.x),
			SC<lyo::SizeType::Window>(d.y),
			SC<lyo::SizeType::Window>(d.w),
			SC<lyo::SizeType::Window>(d.h)
		};
	}
		
	IF_DEBUG
	{
		Engine::Log << "Monitor table\n#\tX\tY\tWidth\tHeight\n";

		for (lyo::size i{ 0 }; i < m_displays.size(); ++i)
		{
			const lyo::Area::Window& m{ m_displays[i] };

			Engine::Log << i + 1 << '\t' << m.x << '\t' << m.y << '\t' << m.width << '\t' << m.height << '\n';
		}

		Engine::Log << '\n';
	}
}

lyo::Engine::~Engine()
{
	IF_DEBUG
	{
		lyo::Engine::Log << "Exiting. Last SDL error: " << (std::strlen(::SDL_GetError()) ? ::SDL_GetError() : "(none)") << '\n';
	}

	::Mix_Quit();
	::TTF_Quit();
	::IMG_Quit();
	::SDL_Quit();
}



const std::vector<lyo::Area::Window>& lyo::Engine::displays() SAFE
{
	return m_displays;
}