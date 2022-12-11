#pragma once

#include <unordered_map>
#include "utility/types.h"

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

	MaxAmount = 255
};

BEGIN_LYO_NAMESPACE
class Mixer
{
	std::unordered_map<Sound, Mix_Chunk*> m_sounds;

public:

	Mixer(int frequency, Uint16 format, int channels, int chunksize);
	~Mixer();
};
END_LYO_NAMESPACE