#include "PlayerHookState.h"

#include "Game/GameInputs.h"
#include "Components/Common/StickOnCollision.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Collider/ColliderComponent.h"
#include "Components/Render/SpriteRenderer.h"

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
	_currentAimState = disconnectState.getAimState();
}

double PlayerHookState::getDegrees()
{
	return disconnectState.getDegrees();
}

AimState& PlayerHookState::getAimState()
{
	return _currentAimState;
}

void PlayerHookState::setAimState(AimState state)
{
	_currentAimState = state;
	disconnectState.setAimState(_currentAimState);
}

std::string PlayerHookState::AimStateName()
{
	switch (_currentAimState)
	{
	case AimState::LEFT:
		return "LEFT";
	case AimState::RIGHT:
			return "RIGHT";
	case AimState::UP:
		return "UP";
	default:
		return "NO DIRECTION";
	}

	return "NO DIRECTION";
}

void PlayerHookState::changeState(Scene& scene, const std::string& stateName)
{
	hookStateManager_->onExit(scene);
	hookStateManager_ = getStateFromName(stateName);
	hookStateManager_->onEnter(scene);
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
	//polymorphism
	hookStateManager_->update(scene);
}


void PlayerHookState::handleEvent(const CollisionEvent& e)
{
	//hook can only be connected if the player is not on a tile.
	if (e.getOtherObject().getType() == GameObject::Type::TILE 
		&& hookStateManager_ == &connectState)
	{
		//was to be used to check if player is on top of a tile.
		bool canDisconnect = false;
		ColliderComponent* tileCollider = e.getOtherObject().getComponent<ColliderComponent>();
		ColliderComponent* playerCollider = owner_.getComponent<ColliderComponent>();

		this->changeState(e.getScene(), "HookDisconnectState");
	}

	if (e.getOtherObject().getType() == GameObject::Type::ENEMY)
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



