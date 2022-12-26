#include "mixer.h"
#include "engine.h"

lyo::Mixer::Mixer(int frequency, Uint16 format, int channels, int chunksize) noexcept
{
	const int result{ ::Mix_OpenAudio(frequency, format, channels, chunksize) };

	IF_DEBUG
		if (result == -1)
			Engine::Crash("Mix_OpenAudio failed!");
}

lyo::Mixer::~Mixer()
{
	::Mix_CloseAudio();
}