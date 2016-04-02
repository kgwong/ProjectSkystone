#include "PlayerMovementState.h"

#include "PlayerState.h"
#include "Application/Log.h"

WalkingState PlayerMovementState::walkingState;
FlyingState PlayerMovementState::flyingState;
AirborneState PlayerMovementState::airborneState;
StunState PlayerMovementState::stunState;
HangState PlayerMovementState::hangState;

PlayerMovementState::PlayerMovementState(GameObject& owner)
	: InputComponent(owner), 
	currentState_(&PlayerMovementState::airborneState)
{
}

PlayerMovementState::~PlayerMovementState()
{
}

void PlayerMovementState::handleInput(Scene& scene, SDL_Event& e)
{
	currentState_->handleInput(scene, owner_, e);
}

void PlayerMovementState::update(Scene& scene)
{
	currentState_->update(scene,owner_);
	//LOG("INFO") << currentState_->name();
}

void PlayerMovementState::changeState(Scene& scene, PlayerState* state)
{
	currentState_->onExit(scene, owner_);
	currentState_ = state;
	currentState_->onEnter(scene, owner_);
}

PlayerState* PlayerMovementState::getState()
{
	return currentState_;
}


