#include <SDL_mixer.h>
#include "mixer.h"
#include "engine.h"

lyo::Mixer::Mixer(int frequency, Uint16 format, int channels, int chunksize)
{
	if (::Mix_OpenAudio(frequency, format, channels, chunksize) == -1)
		Engine::Crash("Mix_OpenAudio failed!");
}

lyo::Mixer::~Mixer()
{

}