#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "SDL/SDL_mixer.h"
#include <string>
#include <memory>

#include "Log.h"
#include "Errors.h"

class AudioPlayer
{
public:
	AudioPlayer();
	~AudioPlayer();

	void LoadClip(std::string path);
	void PlayClip();
private:
	Mix_Chunk * clip_;
};

#endif //AUDIO_PLAYER_H

