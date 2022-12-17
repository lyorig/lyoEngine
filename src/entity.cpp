#include "entity.h"

lyo::Entity::Entity(lyo::Window& window, lyo::cstring filename, const lyo::Coordinate& position, const lyo::AnimatedTexture::InitList animations, const lyo::Size::Texture& frame_size, double scale) noexcept :
	m_texture	{ window, filename, animations, frame_size },
	m_scale		{ scale },
	m_pos		{ position }
{

}



void lyo::Entity::set_position(const lyo::Coordinate& coord) noexcept
{
	m_pos = coord;
}

void lyo::Entity::set_scale(double scale) noexcept
{
	m_scale = scale;
}



lyo::Area::World lyo::Entity::hitbox() SAFE
{
	return lyo::Area::World
	{
		m_pos.x,
		m_pos.y,
		m_texture.width() * m_scale,
		m_texture.height()* m_scale
	};
}