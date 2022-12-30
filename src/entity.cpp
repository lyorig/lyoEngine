#include "entity.h"

lyo::Entity::Entity(lyo::Window& window, const lyo::String& file_name, const lyo::AnimatedTexture::InitList animations, const lyo::Size::Texture& frame_size, const lyo::Coordinate& position, double scale, double time_to_update) noexcept :
	AnimatedTexture	{ window, file_name, animations, frame_size, scale * lyo::Settings::Default_Scale, time_to_update },
	m_pos			{ position }
{

}



void lyo::Entity::update() noexcept
{
	AnimatedTexture::update();

	this->draw(m_pos);
}

void lyo::Entity::set_position(const lyo::Coordinate& position) noexcept
{
	m_pos = position;
}



double lyo::Entity::x() SAFE
{
	return m_pos.x;
}

double lyo::Entity::y() SAFE
{
	return m_pos.y;
}