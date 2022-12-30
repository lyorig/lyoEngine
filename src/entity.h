#pragma once

#include "macros.h"
#include "animated_texture.h"

/* entity.h:
   The base class for objects. */

BEGIN_LYO_NAMESPACE
class Entity : public AnimatedTexture
{
public:

	Entity(lyo::Window& window, const lyo::String& file_name, const lyo::AnimatedTexture::InitList it, const lyo::Size::Texture& frame_size, const lyo::Coordinate& position, double scale = 1.0, double time_to_update = lyo::Settings::Animation_TTU) noexcept;

	virtual void update() noexcept;

	double x() SAFE;
	double y() SAFE;

public: // For debug purposes - make this protected later!

	void set_position(const lyo::Coordinate& position) noexcept;

private:

	lyo::Coordinate	m_pos; // 16b
};
END_LYO_NAMESPACE