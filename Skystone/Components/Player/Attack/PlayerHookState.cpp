#include "PlayerHookState.h"

#include "Game/GameInputs.h"
#include "Components/Common/StickOnCollision.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Player/PlayerControlComponent.h"

#include "Scene/Level/Level.h"
#include "Application/Log.h"

#include "GameMath/CircleMath.h"

PlayerHookState::PlayerHookState(GameObject& owner)
	:InputComponent(owner),
	launchState(owner),
	connectState(owner),
	disconnectState(owner),
	_degrees(0),
	_currentAimState(DEFAULT_AIM_STATE),
	hookStateManager_(&disconnectState)
{
	hanging = false;
	enterOtherLevel = false;
}
PlayerHookState::~PlayerHookState()
{
}

//directional input.
void PlayerHookState::handleInput(Scene& scene, SDL_Event& e)
{

	//POLYMORPHISM
	hookStateManager_->handleInput(scene, e);


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
		_degrees = 270;
	}

	return _degrees;
}

void PlayerHookState::changeState(Scene& scene, const std::string& stateName)
{
	hookStateManager_->onExit(scene);
	hookStateManager_ = getStateFromName(stateName);
	hookStateManager_->onEnter(scene);
}

void PlayerHookState::instantiateHook(Scene& scene)
{
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
			hanging = true;
		}

	}
}

void PlayerHookState::disconnectHook(Scene& scene)
{
	hanging = false;
	if (scene.gameObjects.playerHook != nullptr)
	{
		scene.gameObjects.playerHook->kill();
		scene.gameObjects.playerHook = nullptr;
	}

	if (hookRef != nullptr)
	{
		hookRef->kill();
		hookRef = nullptr;
	}
}

void PlayerHookState::resetState()
{
	//this->changeState()
	hookStateManager_ = &disconnectState;
}

HookStateManager* PlayerHookState::getState()
{
	return hookStateManager_;
}

void PlayerHookState::start(Scene& scene)
{
	launchState.start(scene);
	connectState.start(scene);
	disconnectState.start(scene);
}

void PlayerHookState::update(Scene& scene)
{
	//Level& level = static_cast<Level&>(scene);
	if (hookRef != nullptr && hookStateManager_->name() == disconnectState.name())
		disconnectHook(scene);
	else if (hookRef != nullptr && hookRef->getComponent<StickOnCollision>()->isConnected)
		this->changeState(scene, "HookConnectState");
	
	//polymorphism
	hookStateManager_->update(scene);
	if (hookRef == nullptr && hookStateManager_->name() == launchState.name())
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

	//LOG("INFO") << scene.gameObjects.getPlayer().getComponent<PlayerControlComponent>()->HookState().getState()->name();

}

Point PlayerHookState::getPosition()
{
	return hookRef->getPos();
}

void PlayerHookState::setHanging(bool h)
{
	hanging = h;
}

void PlayerHookState::handleEvent(const CollisionEvent& e)
{
	//hook can only be connected if the player is not on a tile.
	if (e.getOtherObject().getType() == GameObject::Type::TILE 
		&& hookStateManager_ == &connectState)
	{
		this->changeState(e.getScene(), "HookDisconnectState");
	}
}

HookStateManager* PlayerHookState::getStateFromName(const std::string& name)
{
	if (name == launchState.name())
	{
		return &launchState;
	}
	else if (name == connectState.name())
	{
		return &connectState;
	}
	else if (name == disconnectState.name())
	{
		return &disconnectState;
	}
	else
	{
		LOG("ERROR") << "Unknown State";
		return nullptr;
	}
}



