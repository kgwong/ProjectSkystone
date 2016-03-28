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

void PlayerMovementState::handleInput(SDL_Event& e)
{
	currentState_->handleInput(owner_, e);
}

void PlayerMovementState::update(Scene& scene)
{
	currentState_->update(owner_);
	//LOG("INFO") << currentState_->name();
}

void PlayerMovementState::changeState(PlayerState* state)
{
	currentState_->onExit(owner_);
	currentState_ = state;
	currentState_->onEnter(owner_);
}
