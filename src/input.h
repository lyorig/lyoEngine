#pragma once

#include "utility/bitset.h"
#include "types.h"

/* input.h:
   A class which handles input. Now capable of handling
   multiple keypresses in a single update() call. */

BEGIN_LYO_NAMESPACE
class Input
{
	lyo::bitset<SDL_NUM_SCANCODES, lyo::u64> m_pressed, m_held, m_released;

public:

	Input() noexcept;
	DISABLE_COPY_CTORS(Input);

	void update() noexcept;

	bool pressed(SDL_Scancode key) SAFE;
	bool held(SDL_Scancode key) SAFE;
	bool released(SDL_Scancode key) SAFE;
};
END_LYO_NAMESPACE