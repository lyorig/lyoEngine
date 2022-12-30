#pragma once

#include <SDL_mixer.h>

#include "types.h"

#include "utility/slider.h"
#include "utility/capsule.h"

/* music.h:
   Wrapper classes for Mix_Music and Mix_Chunk. */

BEGIN_LYO_NAMESPACE
class Music
{
public:

	Music(lyo::c_string path = nullptr) noexcept;
	
	void operator=(lyo::c_string path) noexcept;

	void play(double time = lyo::Settings::Music_Fade_Time) SAFE;

	void pause()	SAFE;
	void resume()	SAFE;

	void halt(double time = lyo::Settings::Music_Fade_Time) noexcept;

	void set_volume(lyo::ST::Music volume) noexcept;

	operator Mix_Music* () SAFE;

private:

	static Mix_Music* Create(lyo::c_string path) noexcept;

	lyo::Capsule<Mix_Music, ::Mix_FreeMusic> m_music; // 16b

	lyo::VolumeSlider m_volume; // 1b
};



class Chunk
{
public:

	Chunk(lyo::c_string path = nullptr) noexcept;

	void operator=(lyo::c_string path) noexcept;

	void play(lyo::i8 amount_of_loops = 1) SAFE;

	void set_volume(lyo::ST::Music volume) noexcept;

	operator Mix_Chunk* () SAFE;

private:

	static Mix_Chunk* Create(lyo::c_string path) noexcept;

	lyo::Capsule<Mix_Chunk, ::Mix_FreeChunk> m_chunk; // 16b

	lyo::VolumeSlider m_volume;
};
END_LYO_NAMESPACE