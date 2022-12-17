#pragma once

#include <unordered_map>
#include "types.h"

struct Mix_Chunk;

enum class Sound : lyo::u8
{
	MenuClick,
	MenuRelease,

	Footstep,
	MeleeAttackLight,
	MeleeAttackHeavy,

	GunshotLight,
	GunshotMedium,
	GunshotHeavy,

	/* u8 could be larger when using fast integer types, but we'll
	   stick with 255, as we don't want someone accidentally allocating
	   an array of 2,147,483,647 objects. */
	MaxAmount = 255
};

BEGIN_LYO_NAMESPACE
class Mixer
{
	std::unordered_map<Sound, Mix_Chunk*> m_sounds;

public:

	Mixer(int frequency, Uint16 format, int channels, int chunksize) noexcept;
	DISABLE_COPY_CTORS(Mixer);

	~Mixer();
};
END_LYO_NAMESPACE