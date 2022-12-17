#pragma once

#include "algorithm.h"
#include "concepts.h"
#include "../settings.h"
#include "../types.h"
#include "../macros.h"

BEGIN_LYO_NAMESPACE
template <lyo::Arithmetic Slider_type>
class Slider
{
	Slider_type m_value, m_min, m_max;

public:
	constexpr Slider(Slider_type value, Slider_type lower_bound, Slider_type upper_bound) noexcept :
		m_value	{ lyo::Clamp(value, lower_bound, upper_bound) },
		m_min	{ lower_bound },
		m_max	{ upper_bound }
	{

	}



	operator Slider_type() SAFE
	{
		return m_value;
	}

	Slider_type min() SAFE
	{
		return m_min;
	}

	Slider_type max() SAFE
	{
		return m_max;
	}

	bool on_border() SAFE
	{
		return m_value == m_min || m_value == m_max;
	}



	Slider& set_min(Slider_type value) noexcept
	{
		m_value = lyo::Max(m_value, m_min = value);

		return *this;
	}

	Slider& set_max(Slider_type value) noexcept
	{
		m_value = lyo::Min(m_value, m_max = value);

		return *this;
	}



	Slider& operator=(Slider_type value) noexcept
	{
		m_value = lyo::Clamp(value, m_min, m_max);

		return *this;
	}

	Slider& operator+=(Slider_type add) noexcept
	{
		m_value = lyo::Clamp(m_value + add, m_min, m_max);

		return *this;
	}

	Slider& operator-=(Slider_type subtract) noexcept
	{
		m_value = lyo::Clamp(m_value - subtract, m_min, m_max);

		return *this;
	}
};
END_LYO_NAMESPACE