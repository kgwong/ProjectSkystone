#include "GameInputs.h"

#include "Application/Log.h"
#include "Application/Path.h"

#include <fstream>

const Uint8* GameInputs::keyboardState = nullptr;
std::vector<SDL_Keycode> GameInputs::controlMap{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	SDLK_a,
	SDLK_s,
	SDLK_d
};

void GameInputs::init()
{
	keyboardState = SDL_GetKeyboardState(NULL);

	std::ifstream ifs(Path::getFullPath("controls.config"));
	if (!ifs.good())
	{
		LOG("WARNING") << "Failed to open controls.config from" << Path::getBasePath();
		return;
	}

	std::string dummy;
	int decimalForKeyCode;
	//https://wiki.libsdl.org/SDLKeycodeLookup
	for (size_t i = 0; i < controlMap.size(); ++i) 
	{
		ifs >> dummy >> decimalForKeyCode;
		controlMap[i] = static_cast<SDL_Keycode>(decimalForKeyCode);
	}
	
}

bool GameInputs::keyDown(const SDL_Event& e, ControlType control)
{
	return e.type == SDL_KEYDOWN && e.key.keysym.sym == getKeycode(control);
}

bool GameInputs::keyHeld(ControlType control)
{
	SDL_Scancode scancode = SDL_GetScancodeFromKey(getKeycode(control));
	return keyboardState[scancode];
}

bool GameInputs::keyUp(const SDL_Event& e, ControlType control)
{
	return e.type == SDL_KEYUP && e.key.keysym.sym == getKeycode(control);
}

SDL_Keycode GameInputs::getKeycode(ControlType control)
{
	return controlMap[control];
}


