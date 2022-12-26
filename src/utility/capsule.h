#pragma once

#include "../types.h"

/* capsule.h:
   A custom implementation of std::shared_ptr.
   P.S.: Do not even attempt to edit this. Template metaprogramming
   was invented by Hitler himself, and if you asked me why it works, I seriously couldn't tell you. */

BEGIN_LYO_NAMESPACE
template <typename Type, lyo::Function<void, typename std::conditional<std::is_array_v<Type>, Type, Type*>::type> Deleter = nullptr>
class Capsule
{
	void destroy() noexcept
	{
		COMPILE_IF(Deleter)
			Deleter(m_pointer);

		else COMPILE_IF(std::is_array_v<Type>)
			delete[] m_pointer;

		else delete m_pointer;
	}

	/* If Type is an array, std::remove_extent converts it into the base type. */
	using BaseType		= std::remove_extent<Type>::type;
	using CounterType	= lyo::u32;

	BaseType*		m_pointer;	// 8b
	CounterType*	m_count;	// 8b

public:

	constexpr Capsule(BaseType* pointer = nullptr) noexcept :
		m_pointer	{ pointer },
		m_count		{ new CounterType{ 1 } }
	{

	}

	constexpr Capsule(const Capsule& other) noexcept :
		m_pointer	{ other.m_pointer },
		m_count		{ &(++(*other.m_count)) } // Increment, then get the address.
	{
		if (other.m_pointer)
			*m_count += 1;
	}

	constexpr Capsule& operator=(const Capsule& other) noexcept
	{
		m_pointer	= other.m_pointer;
		m_count		= other.m_count;

		if (other.m_pointer)
			*m_count += 1;

		return *this;
	}

	constexpr Capsule(Capsule&& fwd) noexcept
	{
		this->m_pointer = fwd.m_pointer;
		this->m_count	= fwd.m_count;

		fwd.m_pointer	= RC<BaseType*>(fwd.m_count = nullptr);
	}

	constexpr ~Capsule()
	{
		if (--(*m_count) == 0)
		{
			if (m_pointer)
				this->destroy();

			delete m_count;
		}
	}



	constexpr void operator=(BaseType* pointer) noexcept
	{
		this->destroy();

		m_pointer = pointer;
	}



	constexpr CounterType use_count() SAFE
	{
		return *m_count;
	}

	constexpr operator BaseType* () SAFE
	{
		return m_pointer;
	}

	constexpr BaseType* operator->() SAFE
	{
		return m_pointer;
	}

	constexpr BaseType& operator*() SAFE
	{
		return *m_pointer;
	}
};
END_LYO_NAMESPACE