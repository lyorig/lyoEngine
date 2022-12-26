#pragma once

#include "../macros.h"
#include "../types.h"

BEGIN_LYO_NAMESPACE
class Timer
{
	static const lyo::u32 m_freq; // (static) 4b

	lyo::i64 m_startedAt; // 8b

	lyo::i64 get_tick() SAFE;

public:

	Timer() noexcept;

	Timer& reset() noexcept;

	Timer& operator+=(double time) noexcept;
	Timer& operator-=(double time) noexcept;

	operator double() SAFE;
};
END_LYO_NAMESPACE