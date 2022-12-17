#pragma once

#include "macros.h"
#include "animated_texture.h"

NAMESPACE_DECL(lyo, class Window)

BEGIN_LYO_NAMESPACE
class Entity
{
	lyo::AnimatedTexture	m_texture;
	lyo::Coordinate			m_pos;

	double m_scale;

public:

	Entity(lyo::Window& window, lyo::cstring filename, const lyo::Coordinate& position, const lyo::AnimatedTexture::InitList it, const lyo::Size::Texture& frame_size, double scale = 1.0) noexcept;

	virtual void update() = 0;

	void set_position(const lyo::Coordinate& coord) noexcept;
	void set_scale(double scale) noexcept;

	lyo::Area::World hitbox() SAFE;
};
END_LYO_NAMESPACE