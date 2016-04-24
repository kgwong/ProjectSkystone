#include "PlayerMovementState.h"

#include "PlayerState.h"
#include "Application/Log.h"

#include "ComponentEvents/CollisionEvent.h" 
#include "Game/GameConstants.h"
#include "Components/Collider/ColliderComponent.h"

#include <cassert>

PlayerMovementState::PlayerMovementState(GameObject& owner)
	: InputComponent(owner),
	walkingState(owner),
	flyingState(owner),
	airborneState(owner),
	stunState(owner),
	hangState(owner),
	launchState(owner),
	swingState(owner),
	currentState_(&airborneState)
{
	LOG("FLAPJACKS") << "HI";
	canSwing = true;
	direction = 0;
}

PlayerMovementState::~PlayerMovementState()
{
}

void PlayerMovementState::handleInput(Scene& scene, SDL_Event& e)
{
	currentState_->handleInput(scene, e);
}

void PlayerMovementState::update(Scene& scene)
{
	currentState_->update(scene);
}

void PlayerMovementState::changeState(Scene& scene, const std::string& stateName)
{
	currentState_->onExit(scene);
	currentState_ = getStateFromName(stateName);
	currentState_->onEnter(scene);
}

PlayerState* PlayerMovementState::getState()
{
	return currentState_;
}

void PlayerMovementState::handleEvent(const CollisionEvent & e)
{
	currentState_->handleEvent(e);
	
	if (e.getOtherObject().getType() == GameObject::Type::TILE)
	{
		canSwing = false;
	}
	else
	{
		canSwing = true;
	}
}

void PlayerMovementState::setCanSwing(bool swing)
{
	canSwing = swing;
}

void PlayerMovementState::setDirection(int dir)
{
	direction = dir;
}

PlayerState* PlayerMovementState::getStateFromName(const std::string& name)
{
	if (name == walkingState.name())
	{
		return &walkingState;
	}
	else if (name == flyingState.name())
	{
		return &flyingState;
	}
	else if (name == airborneState.name())
	{
		return &airborneState;
	}
	else if (name == stunState.name())
	{
		return &stunState;
	}
	else if (name == hangState.name())
	{
		return &hangState;
	}
	else if (name == launchState.name())
	{
		return &launchState;
	}
	else if (name == swingState.name())
	{
		return &swingState;
	}
	else
	{
		LOG("ERROR") << "Unknown state";
		assert(false);
		return nullptr;
	}
}

