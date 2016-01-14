#include "PlayerHookState.h"

#include "Controls.h"


#include "Log.h"

PlayerHookState::PlayerHookState(GameObject& owner)
	:InputComponent(owner),
	_degrees(0),
	_launched(false),
	_currentAimState(DEFAULT_AIM_STATE)
{

}
PlayerHookState::~PlayerHookState()
{
}

void PlayerHookState::handleInput(SDL_Event& e)
{
	//key released
	if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[UP])
	{
		_currentAimState = AimState::NONE;
	}
	if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[DOWN])
	{
		_currentAimState = AimState::NONE;
	}
	if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[LEFT])
	{
		_currentAimState = AimState::NONE;
	}
	if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[RIGHT])
	{
		_currentAimState = AimState::NONE;
	}
	

	//key pressed
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[UP])
	{
		_currentAimState = AimState::UP;
	}
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[DOWN])
	{
		_currentAimState = AimState::DOWN;
	}
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[LEFT])
	{
		_currentAimState = AimState::LEFT;
	}
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[RIGHT])
	{
		_currentAimState = AimState::RIGHT;
	}

	//_currentAimState->handleInput(owner_, e);
	if (e.key.keysym.sym == controlMap[LAUNCH_HOOK])
		_launched = true;
}

void PlayerHookState::update(Level& level)
{
	if (_launched)
	{
		int test_velocity = 5;
		level.addPlayerHookAtLocation(owner_.getPos(), test_velocity, _degrees);
	}
}

