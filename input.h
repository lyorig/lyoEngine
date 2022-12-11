#pragma once

#include <SDL_events.h>
#include "lyostl/bitset.h"
#include "utility/types.h"

/* input.h:
   A class which manages input. */

BEGIN_LYO_NAMESPACE
class Input {

	SDL_Event m_event;
	lyo::STL::bitset<SDL_NUM_SCANCODES, lyo::u64> b_pressed, b_held, b_released;

public:

	Input();
	~Input();

	void update();

	bool pressed	(SDL_Scancode key)  const;
	bool held		(SDL_Scancode key)	const;
	bool released	(SDL_Scancode key)	const;
};
END_LYO_NAMESPACE