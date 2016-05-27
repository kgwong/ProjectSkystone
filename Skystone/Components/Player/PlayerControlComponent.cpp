#include "PlayerControlComponent.h"

#include "Application/Log.h"
#include "Components/Render/SpriteAnimator.h"

PlayerControlComponent::PlayerControlComponent(GameObject& owner)
	:InputComponent(owner),
	facingDirection_(FacingDirection::RIGHT),
	movement_(owner), 
	attack_(owner), 
	hooker_(owner)
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

void PlayerControlComponent::start(Scene& scene)
{
	movement_.start(scene);
	attack_.start(scene);
	hooker_.start(scene);
	animationController_.setAnimator(owner_.getComponent<SpriteAnimator>());
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
	animationController_.changeAnimation(movement_, attack_);
	LOG("HARVEY") << movement_.getState()->name();
}

void PlayerControlComponent::changeAttackState(Scene& scene, const std::string& stateName)
{
	attack_.changeState(scene, stateName);
	animationController_.changeAnimation(movement_, attack_);
}

bool PlayerControlComponent::isFacing(FacingDirection facingDirection)
{
	return facingDirection_ == facingDirection;
}

FacingDirection PlayerControlComponent::getFacingDirection()
{
	return facingDirection_;
}

void PlayerControlComponent::setFacingDirection(FacingDirection direction)
{
	facingDirection_ = direction;
	animationController_.updatePlayerSpriteFlip(facingDirection_);
}

void PlayerControlComponent::changeHookState(Scene& scene, const std::string& stateName)
{
	hooker_.changeState(scene, stateName);
	LOG("HARVEY") << hooker_.getState()->name();
}

PlayerHookState& PlayerControlComponent::HookState()
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




