#include "FlyingState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Render/SpriteRenderer.h"

const float FlyingState::FLIGHT_VELOCITY = 5 * 60.0f;

FlyingState::FlyingState(GameObject& owner)
	:PlayerState(owner)
{
}


FlyingState::~FlyingState()
{
}

void FlyingState::onEnter(Scene& scene)
{
	physics_->setVelY(-FLIGHT_VELOCITY);
	renderer_->setSprite("Images/jetcycle.png");
}

void FlyingState::onExit(Scene& scene)
{
}

void FlyingState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyUp(e, JUMP))
	{
		controlComponent_->changeMovementState(scene, "AirborneState");
	}
}

void FlyingState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
	renderer_ = owner_.getComponent<SpriteRenderer>();
}

void FlyingState::update(Scene& scene)
{
	if (!physics_->isFalling())
	{
		controlComponent_->changeMovementState(scene, "WalkingState");
		return;
	}
	physics_->setVelX(0);

	if (GameInputs::keyHeld(LEFT))
	{
		physics_->setVelX(-FLIGHT_VELOCITY);
		renderer_->setFlipHorz(true);
	}
	if (GameInputs::keyHeld(RIGHT))
	{
		physics_->setVelX(FLIGHT_VELOCITY);
		renderer_->setFlipHorz(false);
	}
	if (GameInputs::keyHeld(JUMP))
	{
		physics_->setVelY(0);
	}
	if (GameInputs::keyHeld(UP))
	{
		physics_->setVelY(-FLIGHT_VELOCITY);
	}
	if (GameInputs::keyHeld(DOWN))
	{
		physics_->setVelY(FLIGHT_VELOCITY);
	}
}
