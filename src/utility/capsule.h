#pragma once

#include "../types.h"

/* capsule.h:
   A custom implementation of std::shared_ptr.
   P.S.: Do not even attempt to edit this. Template metaprogramming was invented
   by Hitler himself, and if you were to ask me why it works, I seriously couldn't tell you.
   What Stroustrup said about blowing your leg off in C++ is absolutely true. Thanks, debugger! */

BEGIN_LYO_NAMESPACE
template <typename Type, lyo::Function<void, typename std::conditional_t<std::is_array_v<Type>, Type, Type*>> Deleter = nullptr>
class Capsule
{
public:

	/* If Type is an array, std::remove_extent_t converts it into the base type. */
	using BaseType = std::remove_extent_t<Type>;
	using CounterType = lyo::u32;

	constexpr Capsule() noexcept :
		m_pointer	{ nullptr },
		m_count		{ new CounterType{ 0U } }
	{

	}

	constexpr Capsule(BaseType* pointer) noexcept :
		m_pointer	{ pointer },
		m_count		{ new CounterType{ pointer ? 1U : 0U } } // In case some genius inputs a nullptr.
	{
		
	}

	explicit constexpr Capsule(const Capsule& other) noexcept :
		m_pointer	{ other.m_pointer },
		m_count		{ other.m_count }
	{
		if (other.m_pointer)
			*m_count += 1;
	}

	explicit constexpr Capsule(Capsule&& fwd) noexcept
	{
		m_pointer = fwd.m_pointer;
		m_count = fwd.m_count;

		fwd.m_pointer = RC<BaseType*>(fwd.m_count = nullptr);
	}

	constexpr Capsule& operator=(const Capsule& other) noexcept
	{
		if (this != &other)
		{
			this->destroy();

			m_pointer = other.m_pointer;
			m_count = other.m_count;

			if (m_pointer)
				*m_count += 1;
		}

		return *this;
	}

	constexpr Capsule& operator=(Capsule&& fwd) noexcept
	{
		this->destroy();

		m_pointer	= fwd.m_pointer;
		m_count		= fwd.m_count;

		fwd.m_pointer = RC<BaseType*>(fwd.m_count = nullptr);
		
		return *this;
	}

	constexpr ~Capsule()
	{
		this->destroy();
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

private:

	void destroy() noexcept
	{
		/* If m_pointer is a nullptr, m_count is either also
		   a nullptr or shouldn't be decremented. Short circuiting
		   ensures that it won't be accessed if the former check fails. */

		if (m_pointer && --(*m_count) == 0)
		{
			COMPILE_IF(Deleter)
				Deleter(m_pointer);

			else COMPILE_IF(std::is_array_v<Type>)
					delete[] m_pointer;

			else delete m_pointer;

			delete m_count;
		}
	}

	BaseType*		m_pointer;	// 8b
	CounterType*	m_count;	// 8b
};
END_LYO_NAMESPACE