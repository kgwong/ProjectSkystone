#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
	:clip_(nullptr)
{
	Mix_AllocateChannels(8);
}

AudioPlayer::~AudioPlayer()
{
	Mix_FreeChunk(clip_);
}

void AudioPlayer::LoadClip(std::string path)
{
	clip_ = Mix_LoadWAV(path.c_str());
	if (!clip_)
		printf("Mix_LoadWAV: %s ", Mix_GetError());
}

void AudioPlayer::PlayClip()
{
	if (Mix_PlayChannel(-1, clip_, 5) == -1)
		printf("Mix_PlayChannel: %s", Mix_GetError());
}
