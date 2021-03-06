#include "AudioPlayer.h"
#include <iostream>

struct MusicTags
{
	static std::string bgMusic;
	static std::string laser1;// = "laser1";
	static std::string laser2;// = "laser2";
	static std::string player_hit;// = "player_hit";
	static std::string enemy_hit;// = "enemy_hit";
	static std::string enemy_death;// = "enemy_death";
	static std::string gunShot;
};

std::string MusicTags::bgMusic = "bgMusic";
std::string MusicTags::laser1 = "laser1";
std::string MusicTags::laser2 = "laser2";
std::string MusicTags::gunShot = "gunShot";

struct FileNames
{
	static std::string laser1;// = "Laser_Shoot1.wav";
	static std::string laser2;// = "Laser_Shoot2.wav";
	static std::string bgMusic;
	static std::string christian_shot;
};

std::string FileNames::laser1 = "Laser_Shoot1.wav";
std::string FileNames::laser2 = "Laser_Shoot2.wav";
//std::string FileNames::bgMusic = "canton_Benbient-160.mp3";
std::string FileNames::bgMusic = "junior85_-_03_-_As_It_Happens_pt_4.mp3";
std::string FileNames::christian_shot = "christian_shot.wav";

AudioPlayer::AudioPlayer()
	:clip_(nullptr)
{
	Mix_AllocateChannels(8);
}

AudioPlayer::~AudioPlayer()
{
	Mix_FreeChunk(clip_);
}

void AudioPlayer::LoadClip(std::string path,bool faker)
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

////////////////////////////////////THE VOID/////////////////////////////////////////////////////////////////

void AudioPlayer::SetFilePaths(std::string audiofilepath, std::string musicfilepath)
{
	audioFilePath_ = audiofilepath;
	musicFilePath_ = musicfilepath;
	audioFiles_[MusicTags::laser1] = audiofilepath + FileNames::laser1;
	audioFiles_[MusicTags::laser2] = audiofilepath + FileNames::laser2;
	audioFiles_[MusicTags::bgMusic] = musicfilepath + FileNames::bgMusic;
	audioFiles_[MusicTags::gunShot] = audiofilepath + FileNames::christian_shot;
}

//should load actual music .mp3 files.
Music_Ptr AudioPlayer::LoadMusic()
{
	Mix_Music * temp_music;
	temp_music = Mix_LoadMUS(audioFiles_[MusicTags::bgMusic].c_str());
	if (!temp_music)
	{
		printf("LoadMusic: %s", Mix_GetError());
		return nullptr;
	}

	return Music_Ptr(temp_music);
}

AudioClip_Ptr AudioPlayer::LoadClip(std::string clipname)
{
	Mix_Chunk * temp_clip;
	temp_clip = Mix_LoadWAV(audioFiles_[clipname].c_str());
	if (!temp_clip)
	{
		printf("LoadClip: %s", Mix_GetError());
		return nullptr;
	}
	return AudioClip_Ptr(temp_clip);
}

void AudioPlayer::LoadAllClips()
{
	//make them here
	audioClips_["laser1"] = std::move(LoadClip("laser1"));
	audioClips_["laser2"] = std::move(LoadClip("laser2"));
	audioClips_["gunShot"] = std::move(LoadClip("gunShot"));
	music_ = std::move(LoadMusic());
}

void AudioPlayer::init()
{
	SetFilePaths();
	LoadAllClips();
}

void AudioPlayer::PlayMusic()
{

	if (music_ == nullptr)
	{
		std::cout << "I am empty!" << std::endl;
		music_ = std::move(LoadMusic());
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
	//-1 in second argument means play music forever
	if (Mix_PlayMusic(music_.get(),-1) == -1)
	{
		printf("PlayMusic: %s", Mix_GetError());
	}
}

void AudioPlayer::PlayClip(std::string clipname)
{

	int numTimesRepeat = 1;
	//-1 in first argument means play the first unused channel
	//audioClips_[clipname].get()
	Mix_VolumeChunk(audioClips_[clipname].get(), 5);
	if (Mix_PlayChannel(2, audioClips_[clipname].get(), numTimesRepeat) == -1)
	{
		printf("PlayClip: %s", Mix_GetError());
	}
}

void AudioPlayer::PauseMusic()
{
	if (IsPlaying())
		Mix_PauseMusic();
}

void AudioPlayer::ResumeMusic()
{
	if (!IsPlaying())
		Mix_ResumeMusic();
}

bool AudioPlayer::IsPlaying()
{
	return Mix_PausedMusic() == 0;
}

void AudioPlayer::StopMusic()
{
	Mix_HaltMusic();
}








