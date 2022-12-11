#include "input.h"

lyo::Input::Input() :
	m_event		{},
	b_pressed	{},
	b_held		{},
	b_released	{}
{

}

lyo::Input::~Input()
{

}



void lyo::Input::update()
{
	/* Zero out all the bitsets. */
	b_pressed.clear();
	b_released.clear();

	if (::SDL_PollEvent(&m_event))
	{
		/* Hackjob alert! I edited SDL's Scancode enum to also include mouse presses. */
		const SDL_Scancode key			{ m_event.key.keysym.scancode };
		const SDL_Scancode mouse_button	{ SC<SDL_Scancode>(m_event.button.button) };

		switch (m_event.type)
		{
		case SDL_QUIT:
			std::exit(EXIT_SUCCESS);
			return;

		case SDL_KEYDOWN:
			b_pressed.set(key);
			b_held.set(key);
			break;

		case SDL_KEYUP:
			b_released.set(key);
			b_held.reset(key);
			break;

		case SDL_MOUSEBUTTONDOWN:
			b_pressed.set(mouse_button);
			b_held.set(mouse_button);
			break;

		case SDL_MOUSEBUTTONUP:
			b_released.set(mouse_button);
			b_held.reset(mouse_button);
			break;
		}
	}
}



bool lyo::Input::pressed(SDL_Scancode key) const
{
	return b_pressed[key];
}

bool lyo::Input::held(SDL_Scancode key) const
{
	return b_held[key];
}

bool lyo::Input::released(SDL_Scancode key) const
{
	return b_released[key];
}