#include <SDL_events.h>

#include "input.h"
#include "engine.h"

lyo::Input::Input() noexcept
{

}

void lyo::Input::update() noexcept
{
	m_pressed.clear();
	m_released.clear();

	::SDL_PumpEvents();

	int length;
	const Uint8* kb_state	{ ::SDL_GetKeyboardState(&length) };
	const Uint32 mouse_state{ ::SDL_GetMouseState(NULL, NULL) };

	/* Edit the array to also contain mouse presses. I shouldn't be
	   doing this, as const_cast-ing is usually seen as bad (I think?) */
	for (lyo::u16 i{ 1 }; i < 4; ++i)
		CC<Uint8*>(kb_state)[i] = mouse_state & SDL_BUTTON(i);

	/* The handling itself. */
	for (int i{ 0 }; i < length; ++i)
	{
		if (kb_state[i] && !m_held[i])
		{
			m_pressed.set(i);
			m_held.set(i);	
		}
		else if (!kb_state[i] && m_held[i])
		{
			m_held.reset(i);
			m_released.set(i);
		}
	}
}



bool lyo::Input::pressed(SDL_Scancode key) SAFE
{
	return m_pressed[key];
}

bool lyo::Input::held(SDL_Scancode key) SAFE
{
	return m_held[key];
}

bool lyo::Input::released(SDL_Scancode key) SAFE
{
	return m_released[key];
}