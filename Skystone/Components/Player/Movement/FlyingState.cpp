#include "FlyingState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Render/SpriteAnimator.h"

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
	animator_->setSpriteSheet("Images/jetcycle.png");
	animator_->setTimesToPlay(1);
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
	animator_ = owner_.getComponent<SpriteAnimator>();
}

void FlyingState::update(Scene& scene)
{
	if (!physics_->isFalling())
	{
		controlComponent_->changeMovementState(scene, "IdleState");
		return;
	}
	physics_->setVelX(0);

	if (GameInputs::keyHeld(LEFT))
	{
		physics_->setVelX(-FLIGHT_VELOCITY);
		animator_->setFlipHorz(true);
	}
	if (GameInputs::keyHeld(RIGHT))
	{
		physics_->setVelX(FLIGHT_VELOCITY);
		animator_->setFlipHorz(false);
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
