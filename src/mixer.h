#pragma once

#include <SDL_mixer.h>
#include <unordered_map>

#include "music.h"
#include "types.h"

/* mixer.h:
   A class that manages music and sound effect playback. */

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
	   stick with 255, as we really don't want someone accidentally
	   allocating an array of 2,147,483,647 objects. */
	MaxAmount = 255
};

BEGIN_LYO_NAMESPACE
class Mixer
{
public:

	std::unordered_map<Sound, lyo::Chunk> sfx; // 80b

	lyo::Music music; // 16b

	Mixer(int frequency = lyo::Settings::Music_Frequency, Uint16 format = MIX_DEFAULT_FORMAT, int channels = MIX_DEFAULT_CHANNELS, int chunksize = 2048) noexcept;

	~Mixer();
};
END_LYO_NAMESPACE