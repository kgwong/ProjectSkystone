#include "InitSystems.h"

#include "Path.h"

void initAllSystems()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		MySDL_Error("SDL_Init");

	int flags = IMG_INIT_JPG|IMG_INIT_PNG;
	if ((IMG_Init(flags) & flags) != flags)
		MySDL_Error("IMG_Init"); //IMG_GetError

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) 
		MySDL_Error("Mixer failed to initialize");

	Path::initBasePath();
}

void quitAllSystems()
{
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
}