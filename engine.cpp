#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "engine.h"
#include "utility/types.h"

std::ofstream lyo::Engine::Log{ "lyoEngine output.txt" };

void lyo::Engine::Crash(lyo::cstring title, lyo::cstring description)
{
	// We don't want to display an empty string as the description.
	lyo::cstring sdl_error{ std::strlen(description) ? description : "No application error registered." };

	Engine::Log	<< "[CRASH] lyoEngine crashed! Reason: " << title
					<< "\nLast SDL error:" << sdl_error << '\n';

	const SDL_MessageBoxButtonData buttons[2]{ { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Exit" },
											   { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Run anyway" } };

	const SDL_MessageBoxData msgbox{ SDL_MESSAGEBOX_ERROR, NULL, title, sdl_error, 2, buttons, NULL };

	int response{ 0 };

	if (::SDL_ShowMessageBox(&msgbox, &response) < 0)
		Engine::Log << "[CRASH HANDLER] SDL_ShowMessageBox failed. The engine will preventively crash.\n";

	// Assume the response hasn't changed if the message box failed to create.
	if (!response)
		std::exit(EXIT_FAILURE);
}



lyo::Engine::Engine(unsigned init_flags)
{
	/* Initialize everything. */
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

	v_displays.resize(SC<size_t>(displays));

	for (int i{ 0 }; i < displays; ++i)
		if (::SDL_GetDisplayBounds(i, &v_displays.back()) < 0)
			Engine::Crash("SDL_GetDisplayBounds failed!");

	IF_DEBUG
	{
		for (size_t i{ 0 }; i < v_displays.size(); ++i)
		{
			const SDL_Rect display{ v_displays[i] };

			std::cout << "Display " << i << ":\n" << "X: " << display.x << "\nY: " << display.y << "\nWidth: " << display.w << "\nHeight: " << display.h << '\n';
		}
	}
}

lyo::Engine::~Engine()
{
	::Mix_Quit();
	::TTF_Quit();
	::IMG_Quit();
	::SDL_Quit();
}



const std::vector<SDL_Rect>& lyo::Engine::displays() const
{
	return v_displays;
}