#ifndef CONTROLS_H
#define CONTROLS_H

#include <vector>

#include <SDL\SDL.h>

//added hook controls d to launch hook.

enum ControlType
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	JUMP = 4,
	ATTACK = 5,
	LAUNCH_HOOK = 6,
	RETURN = 7
};

class GameInputs {

public: 
	static void init();

	static bool keyDown(const SDL_Event& e, ControlType control);
	static bool keyHeld(ControlType control);
	static bool keyUp(const SDL_Event& e, ControlType control);
	static SDL_Keycode getKeycode(ControlType control);

private:
	static std::vector<SDL_Keycode> controlMap;
	static const Uint8* keyboardState;
};




#endif //CONTROLS_H
