#include "PlayerControlComponent.h"

#include "Application/Log.h"

PlayerControlComponent::PlayerControlComponent(GameObject& owner)
	:InputComponent(owner), movement_(owner), attack_(owner), hooker_(owner)
{	
}


PlayerControlComponent::~PlayerControlComponent()
{
}

void PlayerControlComponent::handleInput(SDL_Event& e)
{
	movement_.handleInput(e);
	attack_.handleInput(e);
	hooker_.handleInput(e);
	HookKeyInput = e.key.keysym.sym;
}

void PlayerControlComponent::update(Scene& scene)
{
	movement_.update(scene);
	attack_.update(scene);
	hooker_.update(scene);
}

void PlayerControlComponent::changeMovementState(PlayerState* state)
{
	movement_.changeState(state);
}

void PlayerControlComponent::changeAttackState(PlayerAimState* state)
{
	attack_.changeState(state);
}


