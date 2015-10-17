#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SDL/SDL_mixer.h>

#include <string>

#include "Errors.h"

class MusicPlayer
{
public:
	MusicPlayer();
	~MusicPlayer();

	void loadSong(const std::string& filePath);

	void play();
	bool isPlaying();

	void pause();
	void resume();
	void stop();

private:
	Mix_Music* song;
};

#endif //MUSICPLAYER_H

