#include "MusicPlayer.h"


MusicPlayer::MusicPlayer()
	:song(nullptr)
{
}


MusicPlayer::~MusicPlayer()
{
	Mix_FreeMusic(song);
}

void MusicPlayer::loadSong(const std::string& filepath)
{
	song = Mix_LoadMUS(filepath.c_str());

	if (song == nullptr)
		MySDL_Error("song failed to load");
}

void MusicPlayer::play()
{
	if (Mix_PlayMusic(song, -1) < 0)
		MySDL_Error("music can't play");
}

bool MusicPlayer::isPlaying()
{
	return Mix_PlayingMusic() != 0;
}

void MusicPlayer::pause()
{
	if (!Mix_PausedMusic())
		Mix_PauseMusic();
}

void MusicPlayer::resume()
{
	if (Mix_PausedMusic())
		Mix_ResumeMusic();
}

void MusicPlayer::stop()
{
	Mix_HaltMusic();
}