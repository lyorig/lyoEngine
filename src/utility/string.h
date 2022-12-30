#pragma once

#include "capsule.h"
#include "concepts.h"

#include "../types.h"

/* string.h:
   Custom implementation of std::string, implemented with
   lyo::Capsule, which should(!) make copying more efficient. */

BEGIN_LYO_NAMESPACE
template <lyo::Character Char>
class BasicString
{
public:

	constexpr static lyo::size Length(const Char* string) noexcept
	{
		COMPILE_IF(std::is_same_v<Char, char>)
			return std::strlen(string);

		else COMPILE_IF(std::is_same_v<Char, wchar_t>)
			return std::wcslen(string);

		else return std::char_traits<Char>::length();
	}

	constexpr BasicString() noexcept :
		m_length{ 0 },
		m_string{ Alloc(0) }
	{

	}

	constexpr BasicString(const Char* string) noexcept :
		m_length{ BasicString::Length(string) },
		m_string{ Alloc(m_length) }
	{
		this->copy(string);
	}

	constexpr BasicString(lyo::size length, Char fill = SC<Char>('\0')) noexcept :
		m_length{ length },
		m_string{ Alloc(length, fill) }
		
	{

	}

	constexpr BasicString operator+(const BasicString& add) noexcept
	{
		return BasicString{ m_string } += add;
	}

	constexpr BasicString& operator+=(const BasicString& add) noexcept
	{
		Char* buf{ Alloc(m_length + add.m_length) };

		std::memcpy(buf, m_string, m_length * sizeof(Char));
		std::memcpy(buf + m_length, add, add.m_length * sizeof(Char));

		m_string = buf;

		m_length += add.m_length;

		return *this;
	}

	constexpr bool operator==(const BasicString& cmp) SAFE
	{
		if (m_length != cmp.length())
			return false;

		for (lyo::size i{ 0 }; i < m_length; ++i)
			if (m_string[i] != cmp[i])
				return false;

		return true;
	}



	constexpr lyo::size length() SAFE
	{
		return m_length;
	}



	constexpr operator const Char* () SAFE
	{
		return m_string;
	}

private:

	constexpr static Char* Alloc(lyo::size length, Char fill = SC<Char>('\0')) noexcept
	{
		return new Char[length + 1](SC<Char>(fill));
	}

	constexpr void copy(const Char* str, lyo::size position = 0) SAFE
	{
		std::memcpy(m_string + position, str, BasicString::Length(str) * sizeof(Char));
	}

	lyo::size				m_length; // 8b
	lyo::Capsule<Char[]>	m_string; // 16b	
};

using String		= BasicString<char>;
using WideString	= BasicString<wchar_t>;
END_LYO_NAMESPACE