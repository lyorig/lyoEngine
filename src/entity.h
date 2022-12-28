#pragma once

#include "macros.h"
#include "animated_texture.h"

/* entity.h:
   The base class for objects. */

BEGIN_LYO_NAMESPACE
class Entity : public AnimatedTexture
{
	lyo::Coordinate	m_pos; // 16b

public: // For debug purposes - make this protected later!

	void set_position(const lyo::Coordinate& position) noexcept;
	
public:

	Entity(lyo::Window& window, lyo::c_string file_name, const lyo::AnimatedTexture::InitList it, const lyo::Size::Texture& frame_size, const lyo::Coordinate& position, double scale = 1.0, double time_to_update = lyo::Settings::Animation_TTU) noexcept;

	virtual void update() noexcept;

	double x() SAFE;
	double y() SAFE;
};
END_LYO_NAMESPACE