#include "PlayerMovementState.h"

#include "PlayerState.h"
#include "Log.h"

WalkingState PlayerMovementState::walkingState;
FlyingState PlayerMovementState::flyingState;
AirborneState PlayerMovementState::airborneState;
StunState PlayerMovementState::stunState;

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

void PlayerMovementState::update(Level& level)
{
	LOG << "Movement";
	currentState_->update(owner_);
}

void PlayerMovementState::changeState(PlayerState* state)
{
	currentState_->onExit(owner_);
	currentState_ = state;
	currentState_->onEnter(owner_);
}
