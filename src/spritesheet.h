#pragma once

#include <unordered_map>

#include "types.h"
#include "surface.h"

/* spritesheet.h:
   A simple class that holds "frames" of a sprite.
   Useful in animations, tilemaps etc. */

BEGIN_LYO_NAMESPACE
class Spritesheet
{
public:

	using FrameRow = std::vector<lyo::Size::Texture>;

private:

	std::vector<FrameRow> m_spritesheet;

public:

	Spritesheet(const lyo::Surface& surface, const lyo::Size::Texture& frame_size) noexcept;

	/* Returns the amount of horizontal and vertical animations. */
	lyo::Size::Animation size() SAFE;

	const FrameRow& operator[](lyo::ST::Animation index) SAFE;
};
END_LYO_NAMESPACE