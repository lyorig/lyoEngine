#include "spritesheet.h"

lyo::Spritesheet::Spritesheet(const lyo::Surface& surface, const lyo::Size::Texture& frame_size) noexcept :
	m_spritesheet{SC<lyo::size>(surface.height() / frame_size.y) }
{
	
}