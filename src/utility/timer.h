#pragma once

#include "../macros.h"
#include "../types.h"

BEGIN_LYO_NAMESPACE
class Timer
{
	lyo::i64 m_startedAt;
	static const lyo::u32 s_freq;

	lyo::i64 get_tick() SAFE;

public:

	Timer() noexcept;

	Timer& reset() noexcept;

	Timer& operator+=(double time) noexcept;
	Timer& operator-=(double time) noexcept;

	operator double() SAFE;
};
END_LYO_NAMESPACE