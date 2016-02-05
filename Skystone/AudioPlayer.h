#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "SDL/SDL_mixer.h"
#include <string>
#include <memory>
#include <map>

#include "Log.h"
#include "Errors.h"
#include "Path.h"

/* DESCRIPTION ------------------- from MSDN

	A unique_ptr does not share its pointer. It cannot be copied to another unique_ptr, passed by value to a function,
	or used in any Standard Template Library (STL) algorithm that requires copies to be made.
	A unique_ptr can only be moved. This means that the ownership of the memory resource is transferred to another unique_ptr
	and the original unique_ptr no longer owns it. We recommend that you restrict an object to one owner, because multiple ownership 
	adds complexity to the program logic. Therefore, when you need a smart pointer for a plain C++ object, use unique_ptr, 
	and when you construct a unique_ptr, use the make_unique helper function.

	"Moving" transfers ownership to a new unique_ptr and resets the old unique_ptr.

*/

//use unique ptr or shared ptr.

//destroyer functors required for unique_ptrs
struct MusicDestroyer
{
	void operator()(Mix_Music * music)
	{
		Mix_FreeMusic(music);
	}
	
};

struct ClipDestroyer
{
	void operator()(Mix_Chunk * chunk)
	{
		Mix_FreeChunk(chunk);
	}
};

//aliases for pointers
//http://stackoverflow.com/questions/17906325/unique-ptr-is-not-getting-init-with-default-deleter
typedef std::unique_ptr<Mix_Music,MusicDestroyer> Music_Ptr;
typedef std::unique_ptr<Mix_Chunk,ClipDestroyer> AudioClip_Ptr;//use unique_ptrs constructor

class AudioPlayer
{
public:
	//constructors
	AudioPlayer();
	~AudioPlayer();

	//initialization
	void SetFilePaths
	(
		std::string audiofilepath = Path::getFullPath("Audio/Clips/"),
		std::string musicfilepath = Path::getFullPath("Audio/Music/")
	);
	Music_Ptr LoadMusic();
	AudioClip_Ptr LoadClip(std::string clipname);
	void LoadAllClips();

	//AudioClip picker ???
	std::shared_ptr<Mix_Chunk> SelectClip(std::string clipname);

	//Audio players
	void PlayMusic();
	void PlayClip(std::string clipname);
	
	//audio controls
	void PauseMusic();
	void ResumeMusic();
	bool IsPlaying();
	void StopMusic();


	//tester methods
	void LoadClip(std::string path,bool faker);
	void PlayClip();
private:
	Mix_Chunk * clip_;

	//       <MusicTag, FullFilePaths>
	std::map<std::string, std::string> audioFiles_;//holds filepaths for audioclips and music.

	//       <MusicTag,   AudioClip_Ptr>
	std::map<std::string, AudioClip_Ptr> audioClips_;//holds unique_ptrs to audio clips

	//current clip to be played.
	//std::shared_ptr<Mix_Chunk> currentClip_;

	//main music clip playing in background;
	Music_Ptr music_;

	//filepaths
	std::string musicFilePath_;
	std::string audioFilePath_;

};

#endif //AUDIO_PLAYER_H

