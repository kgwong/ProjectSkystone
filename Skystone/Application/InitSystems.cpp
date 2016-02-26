#include "InitSystems.h"

#include "Path.h"
#include "Log.h"

void initAllSystems()
{
	Path::initBasePath();
	Log::init();
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		MySDL_Error("SDL_Init");

	int flags = IMG_INIT_JPG|IMG_INIT_PNG;
	if ((IMG_Init(flags) & flags) != flags)
		MySDL_Error("IMG_Init"); //IMG_GetError

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) 
		MySDL_Error("Mixer failed to initialize");
	if (TTF_Init() == -1)
		MySDL_Error("Text failed to initialize");
}

void quitAllSystems()
{
	Mix_CloseAudio();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}