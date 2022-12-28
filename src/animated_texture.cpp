#include "engine.h"
#include "spritesheet.h"
#include "animated_texture.h"

lyo::AnimatedTexture::AnimatedTexture(const lyo::Window& window, lyo::c_string file_name, const InitList& animations, const lyo::Size::Texture& frame_size, double scale, double time_to_update) noexcept :
	Texture			{ window, file_name, scale },
	m_timeToUpdate	{ time_to_update },
	m_animation		{ animations.begin()->first },
	m_frame			{ 0 }
{
	/* Split the texture into frames right off the bat. */
	lyo::Spritesheet		sheet	{ file_name, frame_size };
	lyo::Size::Animation	size	{ sheet.size() };

	FrameVector	frames;

	lyo::Size::Animation pos{ 0, 0 };

	for (auto& pair : animations)
	{
		frames.clear();
		frames.resize(pair.second);

		/* Iterate through the texture frames for every animation. */
		for (lyo::ST::Animation frame{ 0 }; frame < pair.second && pos.y < size.y; ++frame, ++pos.x)
		{
			/* Wrap-around if the horizontal end of the texture is reached. */
			if (pos.x >= size.x)
			{
				pos.x = 0;	// Move back to the left of the texture.
				pos.y += 1;	// Move down one row.
			}

			frames[frame] = sheet[pos.y][pos.x];
		}

		m_spritesheet.insert(std::make_pair(pair.first, frames));
	}

	this->set_area({ 0, 0, frame_size.x, frame_size.y });
}



void lyo::AnimatedTexture::update() noexcept
{
	if (m_animationTimer >= m_timeToUpdate)
	{
		{
			double rem{ m_animationTimer - m_timeToUpdate };
			m_animationTimer.reset() += rem;
		}
	
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