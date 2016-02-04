#include "PlayerHookState.h"

#include "Game/Controls.h"


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


	//------ shooting hook at a direction -------//
	//key released
	//if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[UP])
	//{
	//	_currentAimState = AimState::NONE;
	//}
	////if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[DOWN])
	////{
	////	_currentAimState = AimState::NONE;
	////}
	//if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[LEFT])
	//{
	//	_currentAimState = AimState::NONE;
	//}
	//if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[RIGHT])
	//{
	//	_currentAimState = AimState::NONE;
	//}
	//

	//key pressed
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[UP])
	{
		_currentAimState = AimState::UP;
	}
	
	if (_currentAimState == AimState::UP)
	{
		//UP LEFT SHOT

		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[LEFT])
		{
			_currentAimState = AimState::UP_LEFT;
		}
		//UP RIGHT SHOT
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[RIGHT])
		{
			_currentAimState = AimState::UP_RIGHT;
		}
		else
			_currentAimState = AimState::UP;
	}
	//if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[DOWN])
	//{
	//	_currentAimState = AimState::DOWN;
	//}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[LEFT])
	{
		_currentAimState = AimState::LEFT;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[RIGHT])
	{
		_currentAimState = AimState::RIGHT;
	}

	//_currentAimState->handleInput(owner_, e);
	if (e.key.keysym.sym == controlMap[LAUNCH_HOOK])
		_launched = true;

	//audio testing stuff
	//if (e.key.keysym.sym == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1)
	//{
	//	_audio.PlayClip(AudioPlayer::ClipName::LASER);
	//}
	//if (e.key.keysym.sym == SDL_KEYDOWN  && e.key.keysym.sym == SDLK_2)
	//	_audio.Pause();
}

double PlayerHookState::getDegrees()
{
	switch (_currentAimState)
	{
	case AimState::UP:
		return 270;
		break;
	case AimState::LEFT:
		return 180;
		break;
	case AimState::RIGHT:
		return 0;
		break;
	case AimState::UP_LEFT:
		return 225;
		break;
	case AimState::UP_RIGHT:
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
	}
}

