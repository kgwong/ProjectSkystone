#include "PlayerControlComponent.h"

#include "Application/Log.h"

PlayerControlComponent::PlayerControlComponent(GameObject& owner)
	:InputComponent(owner), movement_(owner), attack_(owner), hooker_(owner)
{	
}


PlayerControlComponent::~PlayerControlComponent()
{ 
}

void PlayerControlComponent::handleInput(Scene& scene, SDL_Event& e)
{
	movement_.handleInput(scene, e);
	attack_.handleInput(scene, e);
	hooker_.handleInput(scene, e);
	HookKeyInput = e.key.keysym.sym;
}

void PlayerControlComponent::update(Scene& scene)
{
	movement_.update(scene);
	attack_.update(scene);
	hooker_.update(scene);

}

void PlayerControlComponent::changeMovementState(Scene& scene, const std::string& stateName)
{
	movement_.changeState(scene, stateName);
	LOG("HARVEY") << movement_.getState()->name();
}

void PlayerControlComponent::changeAttackState(Scene& scene, const std::string& stateName)
{
	attack_.changeState(scene, stateName);
}

void PlayerControlComponent::changeHookState(Scene& scene, const std::string& stateName)
{
	hooker_.changeState(scene, stateName);
	LOG("HARVEY") << hooker_.getState()->name();
}

PlayerHookState PlayerControlComponent::HookState()
{
	return hooker_;
}

PlayerMovementState& PlayerControlComponent::MovementState()
{
	return movement_;
}

PlayerAttackState& PlayerControlComponent::AttackState()
{
	return attack_;
}

void PlayerControlComponent::handleEvent(const CollisionEvent& e)
{
	hooker_.handleEvent(e);
	movement_.handleEvent(e);
}




