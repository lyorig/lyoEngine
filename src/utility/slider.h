#pragma once

#include "concepts.h"
#include "algorithm.h"
#include "../types.h"
#include "../settings.h"

/* slider.h:
   A variable with a minimum and maximum value. */

BEGIN_LYO_NAMESPACE
template <lyo::Arithmetic Slider_type>
class Slider
{
public:

	constexpr Slider(Slider_type lower_bound, Slider_type upper_bound, Slider_type value = SC<Slider_type>((lower_bound + upper_bound) / 2.0)) noexcept :
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

private:

	Slider_type m_value, m_min, m_max; // sizeof(Slider_type) * 3b
};



template <lyo::Arithmetic Slider_type, Slider_type Min, Slider_type Max>
class StaticSlider
{
public:

	constexpr StaticSlider(Slider_type value = SC<Slider_type>((Min + Max) / 2.0)) noexcept :
		m_value{ lyo::Clamp(value, Min, Max) }
	{

	}



	constexpr operator Slider_type() SAFE
	{
		return m_value;
	}

	constexpr Slider_type min() SAFE
	{
		return Min;
	}

	constexpr Slider_type max() SAFE
	{
		return Max;
	}

	constexpr bool on_border() SAFE
	{
		return m_value == Min || m_value == Max;
	}



	constexpr StaticSlider& operator=(Slider_type value) noexcept
	{
		m_value = lyo::Clamp(value, Min, Max);

		return *this;
	}

	constexpr StaticSlider& operator+=(Slider_type add) noexcept
	{
		m_value = lyo::Clamp(m_value + add, Min, Max);

		return *this;
	}

	constexpr StaticSlider& operator-=(Slider_type subtract) noexcept
	{
		m_value = lyo::Clamp(m_value - subtract, Min, Max);

		return *this;
	}

private:

	Slider_type m_value; // sizeof(Slider_type)b
};



using OpacitySlider = StaticSlider<double, 0.0, 255.0>;
using VolumeSlider	= StaticSlider<lyo::ST::Music, 0, 128>;
END_LYO_NAMESPACE