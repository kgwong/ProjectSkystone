#include "LockMovementState.h"

#include "Components/Player/PlayerControlComponent.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Render/SpriteRenderer.h"
#include "Components/Render/SpriteAnimator.h"

#include "WalkingState.h"

LockMovementState::LockMovementState(GameObject& owner)
	:PlayerState(owner)
{
}


LockMovementState::~LockMovementState()
{
}

void LockMovementState::onEnter(Scene& scene)
{
	physics_->setVelX(0);
}

void LockMovementState::onExit(Scene& scene)
{
}

void LockMovementState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyDown(e, JUMP))
	{
		physics_->setVelY(WalkingState::JUMP_VELOCITY); //...
	}
	else if (GameInputs::keyUp(e, UP)) 
	{
		controlComponent_->changeMovementState(scene, "IdleState");
	}
}

void LockMovementState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
	renderer_ = owner_.getComponent<SpriteRenderer>();
	animator_ = owner_.getComponent<SpriteAnimator>();
}

void LockMovementState::update(Scene& scene)
{
	if (physics_->isFalling())
	{
		controlComponent_->changeMovementState(scene, "AirborneState");
		return;
	}
}

std::string LockMovementState::name()
{
	return "LockMovementState";
}
