#include "PlayerControlComponent.h"

#include "Log.h"

PlayerControlComponent::PlayerControlComponent(GameObject& owner)
	:InputComponent(owner), movement_(owner), attack_(owner)
{
}


PlayerControlComponent::~PlayerControlComponent()
{
}

void PlayerControlComponent::handleInput(SDL_Event& e)
{
	movement_.handleInput(e);
	attack_.handleInput(e);
}

void PlayerControlComponent::update(Level& level)
{
	movement_.update(level);
	attack_.update(level);
	//.....add hook_state here.
}

void PlayerControlComponent::changeMovementState(PlayerState* state)
{
	movement_.changeState(state);
}

void PlayerControlComponent::changeAttackState(PlayerAimState* state)
{
	attack_.changeState(state);
}
