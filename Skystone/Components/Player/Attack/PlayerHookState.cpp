#include "PlayerHookState.h"

#include "Game/GameInputs.h"
#include "StickOnCollision.h"
#include "Components/Physics/PhysicsComponent.h"

#include "Scene/Level/Level.h"
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
	if (GameInputs::keyDown(e, UP))
	{
		_currentAimState = AimState::UP;
	}
	else if (GameInputs::keyDown(e, LEFT))
	{
		_currentAimState = AimState::LEFT;
	}
	else if (GameInputs::keyDown(e, RIGHT))
	{
		_currentAimState = AimState::RIGHT;
	}
	if (e.key.keysym.sym == GameInputs::getKeycode(LAUNCH_HOOK))
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

void PlayerHookState::update(Scene& scene)
{
	Level& level = static_cast<Level&>(scene);
	if (_launched)
	{
		int test_velocity = 5;
		_degrees = getDegrees();
		level.addPlayerHookAtLocation(owner_.getPos(), test_velocity, _degrees);
		_launched = false;
		_hookActive = true;
		_degrees = 0;
	}
	
	//StickOnCollision* hook_collision = nullptr;
	//if (level.playerHook)
	//	hook_collision = level.playerHook->getComponent<StickOnCollision>();

	//if (_hookActive)
	//{
	//	if (hook_collision && hook_collision->isConnected)
	//	{
	//		LOG("INFO") << "Hook Position" << level.playerHook->getPos();
	//		Point hookPoint = level.playerHook->getPos();
	//		Point playerPoint = scene.gameObjects.getPlayer().getPos();
	//		scene.gameObjects.getPlayer().getComponent<PhysicsComponent>()->enableGravity(false);
	//		scene.gameObjects.getPlayer().getComponent<PhysicsComponent>()->setAccelX(0.1);
	//		scene.gameObjects.getPlayer().getComponent<PhysicsComponent>()->setAccelY(0.1);
	//	}
	//	else
	//	{
	//		_hookActive = false;
	//		scene.gameObjects.getPlayer().getComponent<PhysicsComponent>()->enableGravity(true);
	//	}
	//	
	//}
	//else
	//{
	//	_hookActive = false;
	//	scene.gameObjects.getPlayer().getComponent<PhysicsComponent>()->enableGravity(true);
	//}

	

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

