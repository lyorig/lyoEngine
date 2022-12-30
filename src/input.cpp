#include <SDL_events.h>

#include "input.h"
#include "engine.h"

lyo::Input::Input() noexcept :
	m_keyboardState{ ::SDL_GetKeyboardState(NULL) }
{

}

void lyo::Input::update() noexcept
{
	m_pressed.clear();
	m_released.clear();

	::SDL_PumpEvents();

	/* Edit the array to also contain mouse presses. I shouldn't be
	doing this, as const_cast-ing is usually seen as bad (I think?) */
	for (Uint32 mouse_state{ ::SDL_GetMouseState(NULL, NULL) }, i{ 1 }; i < 4;
		CC<Uint8*>(m_keyboardState)[i] = mouse_state & SDL_BUTTON(i), ++i);

	/* The handling itself. */
	for (int i{ 0 }; i < SDL_NUM_SCANCODES; ++i)
	{
		if (m_keyboardState[i] && !m_held[i])
		{
			m_pressed.set(i);
			m_held.set(i);	
		}
		else if (!m_keyboardState[i] && m_held[i])
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