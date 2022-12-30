#include "music.h"
#include "engine.h"

Mix_Music* lyo::Music::Create(lyo::c_string path) noexcept
{
	Mix_Music* temp_music{ ::Mix_LoadMUS(path) };

	IF_DEBUG
		if (!temp_music)
			Engine::Crash("Mix_LoadMUS failed!");

	return temp_music;
}



lyo::Music::Music(lyo::c_string path) noexcept :
	m_music	{ path ? Music::Create(path) : nullptr },
	m_volume{ lyo::Settings::Music_Volume }
{

}



void lyo::Music::play(double time) SAFE
{
	const int result{ ::Mix_FadeInMusic(m_music, 0, SC<int>(time * 1000)) };

	IF_DEBUG
		if (result == -1)
			Engine::Crash("Mix_PlayMusic failed!");
}

void lyo::Music::pause() SAFE
{
	IF_DEBUG
		if (!m_music)
			Engine::Warn("Tried to pause nullptr music.");

	if (m_music) ::Mix_PauseMusic();
}

void lyo::Music::resume() SAFE
{
	IF_DEBUG
		if (!m_music)
			Engine::Warn("Tried to resume nullptr music.");

	if (m_music) ::Mix_ResumeMusic();
}



void lyo::Music::halt(double time) noexcept
{
	::Mix_FadeOutMusic(SC<int>(time * 1000));
}



void lyo::Music::set_volume(lyo::ST::Music volume) noexcept
{
	/* This has no way of failing, so no error checking. */
	::Mix_VolumeMusic(m_volume = volume);
}



void lyo::Music::operator=(lyo::c_string path) noexcept
{
	m_music = Music::Create(path);

	this->play();
}



lyo::Music::operator Mix_Music* () SAFE
{
	return m_music;
}



Mix_Chunk* lyo::Chunk::Create(lyo::c_string path) noexcept
{
	Mix_Chunk* temp_chunk{ ::Mix_LoadWAV(path) };

	IF_DEBUG
		if (!temp_chunk)
			Engine::Crash("Mix_LoadWAV failed!");

	return temp_chunk;
}



lyo::Chunk::Chunk(lyo::c_string path) noexcept :
	m_chunk	{ path ? Chunk::Create(path) : nullptr },
	m_volume{ lyo::Settings::Chunk_Volume }
{

}



void lyo::Chunk::operator=(lyo::c_string path) noexcept
{
	m_chunk = Chunk::Create(path);
}



void lyo::Chunk::play(lyo::i8 amount_of_loops) SAFE
{
	const int result{ ::Mix_PlayChannel(-1, m_chunk, amount_of_loops) };

	IF_DEBUG
		if (result == -1)
			Engine::Crash("Mix_PlayChannel failed!");
}



void lyo::Chunk::set_volume(lyo::ST::Music volume) noexcept
{
	IF_DEBUG
		if (!m_chunk)
			Engine::Warn("Tried to set volume of a nullptr chunk.");

	if (m_chunk) ::Mix_VolumeChunk(m_chunk, m_volume = volume);
}



lyo::Chunk::operator Mix_Chunk* () SAFE
{
	return m_chunk;
}