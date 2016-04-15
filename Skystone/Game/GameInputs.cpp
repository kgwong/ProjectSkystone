#include "GameInputs.h"

#include "Application/Log.h"
#include "Application/Path.h"

#include <fstream>
#include <cassert>

namespace 
{
	std::string toString(ControlType type)
	{
		switch (type)
		{
		case UP:
			return "UP";
		case DOWN:
			return "DOWN";
		case LEFT:
			return "LEFT";
		case JUMP:
			return "JUMP";
		case ATTACK:
			return "ATTACK";
		case LAUNCH_HOOK:
			return "LAUNCH_HOOK";
		case RETURN:
			return "RETURN";
		case ESC:
			return "ESC";
		default:
			assert(false);
			return "dummystring";
		}
	}
}

const Uint8* GameInputs::keyboardState = nullptr;
std::vector<SDL_Keycode> GameInputs::controlMap{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	SDLK_a,
	SDLK_s,
	SDLK_d,
	SDLK_RETURN,
	SDLK_ESCAPE
};

void GameInputs::init()
{
	keyboardState = SDL_GetKeyboardState(NULL);

	std::fstream fs(Path::getFullPath("controls.config"));
	if (!fs.good())
	{
		LOG("WARNING") << "Failed to open controls.config from" << Path::getBasePath();
		return;
	}

	std::string dummy;
	int decimalForKeyCode; //https://wiki.libsdl.org/SDLKeycodeLookup
	int count = 0;
	while (fs >> dummy >> decimalForKeyCode)
	{
		controlMap[count++] = static_cast<SDL_Keycode>(decimalForKeyCode);
	}
	fs.clear();
	for (size_t i = count; i < controlMap.size(); ++i)
	{
		fs << std::endl;
		fs << toString(static_cast<ControlType>(i)) << " " << static_cast<int>(controlMap[i]);
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


