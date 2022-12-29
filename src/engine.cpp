#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "engine.h"
#include "globals.h"
#include "settings.h"

std::ofstream lyo::Engine::Log{ "lyoEngine output.txt" };

void lyo::Engine::Warn(lyo::c_string reason) noexcept
{
	static lyo::u32 count{ 0 };

	Engine::Log << "[WARNING] #" << ++count << ": " << reason << " (at " << g::runtime << "s)" << std::endl;
}

void lyo::Engine::Crash(lyo::c_string title, lyo::c_string description) noexcept
{
	/* We don't want to display an empty string as the description. */
	lyo::c_string err{ std::strlen(description) ? description : "(none)" };

	Engine::Log	<< "[CRASH HANDLER] lyoEngine crashed!\nReason: " << title
					<< "\nError: " << err << "\nRuntime: " << g::runtime << std::endl;

	const SDL_MessageBoxButtonData buttons[2]{ { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Exit" },
											   { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Run anyway" } };

	const SDL_MessageBoxData msgbox{ SDL_MESSAGEBOX_ERROR, NULL, title, err, 2, buttons, NULL };

	int response{ 0 };

	if (::SDL_ShowMessageBox(&msgbox, &response) < 0)
		Engine::Log << "[CRASH HANDLER] SDL_ShowMessageBox failed. The engine will preventively crash." << std::endl;

	/* Assume the response hasn't changed if the message box failed to create. */
	if (!response)
		std::exit(EXIT_FAILURE);

	Engine::Log << "[CRASH HANDLER] The user has decided that running the engine in spite of an error is a good idea. God help them." << std::endl;
}



lyo::Engine::Engine(Uint32 init_flags) noexcept
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

	IF_DEBUG
		if (displays < 0)
			Engine::Crash("SDL_GetNumVideoDisplays failed!");

	m_displays.resize(SC<lyo::size>(displays));

	for (int i{ 0 }; i < displays; ++i)
	{
		using Type = lyo::ST::Window;

		SDL_Rect d;

		if (::SDL_GetDisplayBounds(i, &d) < 0)
			Engine::Crash("SDL_GetDisplayBounds failed!");

		m_displays[i] =
		{
			SC<Type>(d.x),
			SC<Type>(d.y),
			SC<Type>(d.w),
			SC<Type>(d.h)
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



const lyo::Engine::DisplayVector& lyo::Engine::displays() SAFE
{
	return m_displays;
}