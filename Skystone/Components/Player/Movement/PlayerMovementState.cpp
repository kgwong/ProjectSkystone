#include "PlayerMovementState.h"

#include "Application/Log.h"

#include "AirborneState.h"
#include "IdleState.h"
#include "WalkingState.h"
#include "CrouchState.h"
#include "FlyingState.h"
#include "StunState.h"
#include "LockMovementState.h"

#include "HangState.h"
#include "LaunchState.h"
#include "SwingState.h"

PlayerMovementState::PlayerMovementState(GameObject& owner)
	: InputComponent(owner)
{
	direction = 0;

	addState(std::make_shared<WalkingState>(owner));
	addState(std::make_shared<CrouchState>(owner));
	addState(std::make_shared<LockMovementState>(owner));
	addState(std::make_shared<FlyingState>(owner));
	addState(std::make_shared<AirborneState>(owner));
	addState(std::make_shared<StunState>(owner));
	addState(std::make_shared<HangState>(owner));
	addState(std::make_shared<LaunchState>(owner));
	addState(std::make_shared<SwingState>(owner));
	addState(std::make_shared<IdleState>(owner));
	currentState_ = getStateFromName("AirborneState");
	previousState_ = getStateFromName("AirborneState");
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
	currentState_->onEnter(scene);
}

void PlayerMovementState::update(Scene& scene)
{
	currentState_->update(scene);
}

void PlayerMovementState::changeState(Scene& scene, const std::string& stateName)
{
	currentState_->onExit(scene);
	previousState_ = currentState_;
	currentState_ = getStateFromName(stateName);
	LOG("Kevin") << "ENTERING: " << currentState_->name();
	currentState_->onEnter(scene);
}

void PlayerMovementState::resetState()
{
	if(currentState_->name() != "FlyingState")
		currentState_ = getStateFromName("AirborneState");
}

PlayerState* PlayerMovementState::getState()
{
	return currentState_;
}

PlayerState* PlayerMovementState::getPrevState()
{
	return previousState_;
}

void PlayerMovementState::handleEvent(const CollisionEvent & e)
{
	currentState_->handleEvent(e);
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
