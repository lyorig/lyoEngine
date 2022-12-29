#pragma once

#include "../macros.h"
#include "../types.h"

/* timer.h:
   A basic system for timing.
   No error checking is present, as functions used here
   will always succeed on systems running Windows XP or later. */

BEGIN_LYO_NAMESPACE
class Timer
{
public:

	Timer() noexcept;

	Timer& reset() noexcept;

	Timer& operator+=(double time) noexcept;
	Timer& operator-=(double time) noexcept;

	operator double() SAFE;

private:

	static lyo::u64 Tick() noexcept;

	static const lyo::u32 m_freq; // (static) 4b

	lyo::u64 m_startedAt; // 8b
};
END_LYO_NAMESPACE