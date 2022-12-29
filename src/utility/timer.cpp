#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>

#include "timer.h"
#include "algorithm.h"

const lyo::u32 lyo::Timer::m_freq
{
	[]()
	{
		LARGE_INTEGER x;
		::QueryPerformanceFrequency(&x);
		return SC<lyo::u32>(x.QuadPart);
	}()
};

lyo::Timer::Timer() noexcept :
	m_startedAt{ Timer::Tick() }
{

}



lyo::Timer& lyo::Timer::reset() noexcept
{
	m_startedAt = Timer::Tick();

	return *this;
}



/* Addition / subtraction functions. */
lyo::Timer& lyo::Timer::operator+=(double time) noexcept
{
	m_startedAt -= lyo::Cast::Unsigned<lyo::u64>(time * m_freq);
	return *this;
}

lyo::Timer& lyo::Timer::operator-=(double time) noexcept
{
	m_startedAt += lyo::Cast::Unsigned<lyo::u64>(time * m_freq);
	return *this;
}



/* Returns the elapsed time. */
lyo::Timer::operator double() SAFE
{
	return SC<double>(Timer::Tick() - m_startedAt) / m_freq;
}



lyo::u64 lyo::Timer::Tick() noexcept
{
	LARGE_INTEGER x;
	::QueryPerformanceCounter(&x);
	return x.QuadPart;
}