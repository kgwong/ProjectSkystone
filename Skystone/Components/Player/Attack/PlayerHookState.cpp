#include "PlayerHookState.h"

#include "Game/GameInputs.h"
#include "StickOnCollision.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Player/PlayerControlComponent.h"

#include "Scene/Level/Level.h"
#include "Application/Log.h"

#include "GameMath/CircleMath.h"

//forward declare
HookLaunchState PlayerHookState::launchState;
HookConnectState PlayerHookState::connectState;
HookDisconnectState PlayerHookState::disconnectState;

PlayerHookState::PlayerHookState(GameObject& owner)
	:InputComponent(owner),
	_degrees(0),
	_launched(false),
	_hookActive(false),
	_currentAimState(DEFAULT_AIM_STATE),
	hookStateManager_(&disconnectState)
{
	hanging = false;
}
PlayerHookState::~PlayerHookState()
{
}

//directional input.
void PlayerHookState::handleInput(SDL_Event& e)
{

	//POLYMORPHISM
	hookStateManager_->handleInput(owner_, e);

	//remove later.
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
	//if (e.key.keysym.sym == GameInputs::getKeycode(LAUNCH_HOOK))
	//{
	//	_launched = true;
	//}
}

double PlayerHookState::getDegrees()
{
	switch (_currentAimState)
	{
	case AimState::UP:
		_degrees = 270;
		break;
	case AimState::LEFT:
		_degrees = 225;
		break;
	case AimState::RIGHT:
		_degrees = 315;
		break;
	default:
		_degrees = 0;//shouldnt go to this default.
	}

	return _degrees;
}

void PlayerHookState::changeState(HookStateManager * state)
{
	hookStateManager_->onExit(owner_);
	hookStateManager_ = state;
	hookStateManager_->onEnter(owner_);
}

void PlayerHookState::instantiateHook(Scene& scene)
{
	_hookActive = true;
	int test_velocity = 5;
	_degrees = getDegrees();
	float leftSideDegree = 225;
	float rightSideDegree = 315;
	float upSideDegree = 270;

	Point hookPosition = scene.gameObjects.getPlayer().getPos();

	//offset.
	if (_degrees == leftSideDegree)
		hookPosition.x -= 20;
	else if (_degrees == rightSideDegree)
		hookPosition.x += 30;
	else if (_degrees == upSideDegree)
		hookPosition.y -= 50;

	hookRef = scene.gameObjects.add("PlayerHook", "Player Hook", hookPosition);
	
	float testVel = 5.0f;
	float newVelX = (float)(testVel * cos(toRadians(getDegrees())));
	float newVelY = (float)(testVel * sin(toRadians(getDegrees())));
	hookRef->getComponent<PhysicsComponent>()->enableGravity(false);
	hookRef->getComponent<PhysicsComponent>()->setVelX(newVelX * 60.0f);
	hookRef->getComponent<PhysicsComponent>()->setVelY(newVelY * 60.0f);
	//scene.gameObjects.setHook(hookRef.get());
}

void PlayerHookState::connectHook(Scene& scene)
{
	StickOnCollision* hook_collision = nullptr;
	if (scene.gameObjects.playerHook != nullptr)
		hook_collision = scene.gameObjects.playerHook->getComponent<StickOnCollision>();

	if (hook_collision != nullptr)
	{
		if (hook_collision->isConnected)
		{
			hookRef->getComponent<PhysicsComponent>()->setVelX(0.0f);
			hookRef->getComponent<PhysicsComponent>()->setVelY(0.0f);
		/*	auto playerPhysics = owner_.getComponent<PhysicsComponent>();
			playerPhysics->setVelY(0);
			playerPhysics->enableGravity(false);*/
			hanging = true;
		}

	}
}

void PlayerHookState::disconnectHook(Scene& scene)
{
	hanging = false;
	_hookActive = false;
	if (scene.gameObjects.playerHook != nullptr)
	{
		scene.gameObjects.playerHook->kill();
		scene.gameObjects.playerHook = nullptr;
		hookRef = nullptr;
	}
}

void PlayerHookState::resetState()
{
	hookStateManager_ = &disconnectState;
}

HookStateManager* PlayerHookState::getState()
{
	return hookStateManager_;
}

void PlayerHookState::update(Scene& scene)
{
	//Level& level = static_cast<Level&>(scene);
	if (hookRef != nullptr && hookStateManager_->name() == disconnectState.name())
		disconnectHook(scene);
	else if (hookRef != nullptr && hookRef->getComponent<StickOnCollision>()->isConnected)
		this->changeState(&connectState);
	
	//polymorphism
	hookStateManager_->update(owner_);
	if (scene.gameObjects.playerHook == nullptr && hookStateManager_->name() == launchState.name())
	{
		instantiateHook(scene);
	}
	else if (hookStateManager_->name() == connectState.name())
	{ 
		connectHook(scene); 
	}
	else if (hookRef != nullptr && hookStateManager_->name() == disconnectState.name())
	{
		disconnectHook(scene);
	}

	//LOG("INFO") << hookStateManager_->name();

	//if (_launched && !_hookActive)
	//{
	//	int test_velocity = 5;
	//	_degrees = getDegrees();
	//	float leftSideDegree = 225;
	//	float rightSideDegree = 315;
	//	float upSideDegree = 270;

	//	Point hookPosition = scene.gameObjects.getPlayer().getPos();		

	//	//offset.
	//	if (_degrees == leftSideDegree)
	//		hookPosition.x -= 10;
	//	else if (_degrees == rightSideDegree)
	//		hookPosition.x += 10;
	//	else if (_degrees == upSideDegree)
	//		hookPosition.y -= 10;

	//	auto playerHook = scene.gameObjects.add("PlayerHook", "Player Hook",hookPosition);
	//	auto physics = playerHook->getComponent<PhysicsComponent>();
	//	float newVelX = (float)(test_velocity * cos(toRadians(_degrees)));
	//	float newVelY = (float)(test_velocity * sin(toRadians(_degrees)));
	//	physics->enableGravity(false);
	//	physics->setVelX(newVelX * 60.0f);
	//	physics->setVelY(newVelY * 60.0f);
	//	_launched = false;
	//	_hookActive = true;
	//	_degrees = 0;	
	//}
	
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

Point PlayerHookState::getPosition()
{
	return hookRef->getPos();
}


//delete
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


