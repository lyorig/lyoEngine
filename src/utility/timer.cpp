#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>
#include "timer.h"
#include "algorithm.h"

const lyo::u32 lyo::Timer::m_freq
{
	[]() {
		LARGE_INTEGER li;
		::QueryPerformanceFrequency(&li);
		return SC<lyo::u32>(li.QuadPart);
	}()
};

lyo::Timer::Timer() noexcept :
	m_startedAt{ this->get_tick() }
{

}



lyo::Timer& lyo::Timer::reset() noexcept
{
	m_startedAt = this->get_tick();

	return *this;
}



/* Addition / subtraction functions. */
lyo::Timer& lyo::Timer::operator+=(double time) noexcept
{
	m_startedAt -= lyo::Cast::Signed<lyo::i64>(time * m_freq);
	return *this;
}

lyo::Timer& lyo::Timer::operator-=(double time) noexcept
{
	m_startedAt += lyo::Cast::Signed<lyo::i64>(time * m_freq);
	return *this;
}



/* Returns the elapsed time. */
lyo::Timer::operator double() SAFE
{
	return SC<double>(this->get_tick() - m_startedAt) / m_freq;
}



lyo::i64 lyo::Timer::get_tick() SAFE
{
	LARGE_INTEGER li;
	::QueryPerformanceCounter(&li);
	return li.QuadPart;
}