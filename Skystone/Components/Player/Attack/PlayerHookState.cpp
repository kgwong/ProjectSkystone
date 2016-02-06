#include "PlayerHookState.h"

#include "Game/Controls.h"


#include "Application/Log.h"

PlayerHookState::PlayerHookState(GameObject& owner)
	:InputComponent(owner),
	_degrees(0),
	_launched(false),
	_hookActive(false),
	_currentAimState(DEFAULT_AIM_STATE)
{
	
}
PlayerHookState::~PlayerHookState()
{
}

void PlayerHookState::handleInput(SDL_Event& e)
{

	_keyInput = e.key.keysym.sym;

	//key pressed
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[UP])
	{
		_currentAimState = AimState::UP;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[LEFT])
	{
		_currentAimState = AimState::LEFT;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[RIGHT])
	{
		_currentAimState = AimState::RIGHT;
	}
	if (e.key.keysym.sym == controlMap[LAUNCH_HOOK])
	{
		_launched = true;
	}
}

double PlayerHookState::getDegrees()
{
	switch (_currentAimState)
	{
	case AimState::UP:
		return 270;
		break;
	case AimState::LEFT:
		return 225;
		break;
	case AimState::RIGHT:
		return 315;
		break;
	default:
		return -9999;//shouldnt go to this default.
	}
}

void PlayerHookState::update(Level& level)
{
	if (_launched)
	{
		int test_velocity = 5;
		_degrees = getDegrees();
		level.addPlayerHookAtLocation(owner_.getPos(), test_velocity, _degrees);
		_launched = false;
		_hookActive = true;
		_degrees = 0;
	}

	if (_hookActive)
	{
		
	}
	

}

void PlayerHookState::setLaunched(bool b)
{
	_launched = b;
}

bool PlayerHookState::hasLaunched()
{
	return _launched;
}

bool PlayerHookState::isActiveHook()
{
	return _hookActive;
}

SDL_Keycode PlayerHookState::getKeyInput()
{
	return _keyInput;
}

