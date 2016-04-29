#include "PlayerMovementState.h"

#include "PlayerState.h"
#include "Application/Log.h"

#include "ComponentEvents/CollisionEvent.h" 
#include "Game/GameConstants.h"
#include "Components/Collider/ColliderComponent.h"

#include <cassert>

PlayerMovementState::PlayerMovementState(GameObject& owner)
	: InputComponent(owner)
{
	LOG("FLAPJACKS") << "HI";
	canSwing = true;
	direction = 0;

	addState(std::make_shared<WalkingState>(owner));
	addState(std::make_shared<LockMovementState>(owner));
	addState(std::make_shared<FlyingState>(owner));
	addState(std::make_shared<AirborneState>(owner));
	addState(std::make_shared<StunState>(owner));
	addState(std::make_shared<HangState>(owner));
	addState(std::make_shared<LaunchState>(owner));
	addState(std::make_shared<SwingState>(owner));
	currentState_ = getStateFromName("AirborneState");
}

PlayerMovementState::~PlayerMovementState()
{
}

void PlayerMovementState::handleInput(Scene& scene, SDL_Event& e)
{
	currentState_->handleInput(scene, e);
}

void PlayerMovementState::start(Scene& scene)
{
	for (auto& s : states_)
	{
		s.second->start(scene);
	}
}

void PlayerMovementState::update(Scene& scene)
{
	currentState_->update(scene);
}

void PlayerMovementState::changeState(Scene& scene, const std::string& stateName)
{
	LOG("Kevin") << "LEAVING: " << currentState_->name();
	currentState_->onExit(scene);
	currentState_ = getStateFromName(stateName);
	LOG("Kevin") << "ENTERING: " << currentState_->name();
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
	if (states_.find(name) != states_.end())
	{
		return states_.at(name).get();
	}
	else
	{
		__debugbreak();
		return nullptr;
	}
}

void PlayerMovementState::addState(std::shared_ptr<PlayerState> state)
{
	states_.insert({ state->name(), state });
}

void PlayerMovementState::setSpeed(float s)
{
	speed = s;
}

void PlayerMovementState::setAngle(float a)
{
	angle = a;
}

void PlayerMovementState::setRadius(float r)
{
	radius = r;
}

