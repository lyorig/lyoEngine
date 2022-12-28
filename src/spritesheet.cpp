#include "engine.h"
#include "spritesheet.h"

lyo::Spritesheet::Spritesheet(const lyo::Surface& surface, const lyo::Size::Texture& frame_size) noexcept :
	m_spritesheet{ SC<lyo::size>(surface.height() / frame_size.y) }
{
	IF_DEBUG
	{
		if (!frame_size.x || !frame_size.y)
			Engine::Crash("Frame-size width and/or height are zero!", "in lyo::Spritesheet constructor");

		if (surface.width() < frame_size.x || surface.height() < frame_size.y)
			Engine::Crash("Surface is smaller than frame size!", "in lyo::Spritesheet constructor");
	}

	using Type = lyo::ST::Texture;

	FrameRow frames{ SC<lyo::size>(surface.width() / frame_size.x) };

	for (lyo::Size::Texture pos{ 0, 0 }; pos.y < m_spritesheet.capacity(); ++pos.x)
	{
		if (pos.x >= frames.capacity())
		{
			m_spritesheet[pos.y] = frames;
			// frames.clear() - This leads to a debug assertion when assigning the size. Why? I have no fucking clue.

			pos.x = 0;
			pos.y += 1;
		}

		frames[pos.x] = { SC<Type>(pos.x * frame_size.x), SC<Type>(pos.y * frame_size.y) };
	}
}



lyo::Size::Animation lyo::Spritesheet::size() SAFE
{
	using Type = lyo::ST::Animation;

	return lyo::Size::Animation
	{
		SC<Type>(m_spritesheet.size()),
		SC<Type>(m_spritesheet[0].size())
	};
}

const lyo::Spritesheet::FrameRow& lyo::Spritesheet::operator[](lyo::ST::Animation index) SAFE
{
	return m_spritesheet[SC<lyo::size>(index)];
}