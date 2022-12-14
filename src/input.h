#pragma once

#include "utility/bitset.h"

/* input.h:
   A class which handles input, capable of handling
   multiple keypresses in a single update() call. */

BEGIN_LYO_NAMESPACE
class Input
{
public:

	Input() noexcept;

	void update() noexcept;

	bool pressed(SDL_Scancode key) SAFE;
	bool held(SDL_Scancode key) SAFE;
	bool released(SDL_Scancode key) SAFE;

private:

	lyo::Bitset<SDL_NUM_SCANCODES, lyo::u64> m_pressed, m_held, m_released;

	const Uint8* m_keyboardState;
};
END_LYO_NAMESPACE