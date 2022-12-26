#include "engine.h"
#include "surface.h"
#include "animated_texture.h"

lyo::AnimatedTexture::AnimatedTexture(const lyo::Window& window, lyo::c_string file_name, const InitList& animations, const lyo::Size::Texture& frame_size, double scale, double time_to_update) noexcept :
	Texture			{ window, file_name, scale },
	m_timeToUpdate	{ time_to_update },
	m_animation		{ animations.begin()->first },
	m_frame			{ 0 }
{
	const lyo::Size::Texture& size{ this->size() };

	this->set_area({ 0, 0, frame_size.x, frame_size.y });

	lyo::ST::Texture x{ 0 }, y{ 0 };

	FrameVector	frames;

	for (auto& pair : animations)
	{
		frames.clear();
		frames.resize(pair.second);

		/* Iterate through the texture frames for every animation. */
		for (lyo::ST::Animation frame{ 0 }; frame < pair.second && y < size.y; ++frame, x += frame_size.x)
		{
			/* Wrap-around if we reach the horizontal end. */
			if (x >= size.x)
			{
				x = 0;
				y += frame_size.y;
			}

			frames[frame] = { x, y };
		}

		m_spritesheet.insert({ pair.first, frames });
	}
}



void lyo::AnimatedTexture::update() noexcept
{
	if (m_animationTimer >= m_timeToUpdate)
	{
		m_animationTimer.reset();

		const FrameVector& frame_vec{ m_spritesheet[m_animation] };

		if (++m_frame >= frame_vec.size())
			m_frame = 0;

		const lyo::Size::Texture& frame{ frame_vec[m_frame] };
		const lyo::Area::Texture& area{ this->area() };

		this->set_area({ frame.x, frame.y, area.width, area.height });	
	}

	Texture::update();
}



void lyo::AnimatedTexture::set_animation(Animation animation) noexcept
{
	m_animation = animation;
}
