#pragma once

#include <unordered_map>

#include "types.h"
#include "surface.h"

BEGIN_LYO_NAMESPACE
class Spritesheet
{
	std::vector<std::vector<lyo::Area::Texture>> m_spritesheet;

public:

	Spritesheet(const lyo::Surface& surface, const lyo::Size::Texture& frame_size) noexcept;
};
END_LYO_NAMESPACE