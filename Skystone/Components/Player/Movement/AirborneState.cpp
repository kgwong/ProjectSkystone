#include "AirborneState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Render/SpriteRenderer.h"

AirborneState::AirborneState(GameObject& owner)
	:PlayerState(owner)
{
}


AirborneState::~AirborneState()
{
}

void AirborneState::onEnter(Scene& scene)
{
	renderer_->setSprite("Images/jump cycle.png");
}

void AirborneState::onExit(Scene& scene)
{
}

void AirborneState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyHeld(JUMP))
	{
		if (GameInputs::keyDown(e, JUMP))
		{
			controlComponent_->changeMovementState(scene, "FlyingState");
		}
	}
	//temp
	if (GameInputs::keyDown(e, DOWN))
	{
		controlComponent_->changeMovementState(scene, "CrouchState");
	}
}

void AirborneState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
	renderer_ = owner_.getComponent<SpriteRenderer>();
}

void AirborneState::update(Scene& scene)
{
	if (controlComponent_->HookState().getState()->name() == "HookConnectState")
	{
		controlComponent_->changeMovementState(scene, "Hang");
		return;
	}
	
	if (!physics_->isFalling())
	{
		controlComponent_->changeMovementState(scene, "WalkingState");
		return;
	}

	if (GameInputs::keyHeld(LEFT))
	{
		physics_->setVelX(-5 * 60.0f);
		renderer_->setFlipHorz(true);
	}
	else if (GameInputs::keyHeld(RIGHT))
	{
		physics_->setVelX(5 * 60.0f);
		renderer_->setFlipHorz(false);
	}
	else
	{
		physics_->setVelX(0);
	}
}

std::string AirborneState::name()
{
	return "AirborneState";
}
