#ifndef CONTROLS_H
#define CONTROLS_H

#include <vector>

#include <SDL\SDL.h>


//added hook controls d to launch hook.

enum Controls
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	JUMP = 4,
	ATTACK = 5,
	LAUNCH_HOOK = 6
};

static std::vector<SDL_Keycode> controlMap{
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	SDLK_a,
	SDLK_s,
	SDLK_d
};

#endif //CONTROLS_H
