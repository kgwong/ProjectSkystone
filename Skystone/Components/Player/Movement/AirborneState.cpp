#include "AirborneState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Render/SpriteRenderer.h"

#include "Resources/Resources.h"

AirborneState::AirborneState(GameObject& owner)
	:PlayerState(owner)
{
}


AirborneState::~AirborneState()
{
}

void AirborneState::onEnter(Scene& scene)
{
	jumpHeld_ = true;
	owner_.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/jump cycle.png"));
}

void AirborneState::onExit(Scene& scene)
{
}

void AirborneState::handleInput(Scene& scene, SDL_Event& e)
{
	if (!jumpHeld_)
	{
		if (GameInputs::keyDown(e, JUMP))
		{
			//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::flyingState);
			owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "FlyingState");
		}
	}
}

void AirborneState::update(Scene& scene)
{
	if (owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name() == "HookConnectState")
	{
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "Hang");
		return;
	}
	
	if (!owner_.getComponent<PhysicsComponent>()->isFalling())
	{
		//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::walkingState);
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "WalkingState");
		return;
	}

	if (GameInputs::keyHeld(LEFT))
	{
		owner_.getComponent<PhysicsComponent>()->setVelX(-5 * 60.0f);
	}
	else if (GameInputs::keyHeld(RIGHT))
	{
		owner_.getComponent<PhysicsComponent>()->setVelX(5 * 60.0f);
	}
	else
	{
		owner_.getComponent<PhysicsComponent>()->setVelX(0);
	}

	jumpHeld_ = GameInputs::keyHeld(JUMP);
}

std::string AirborneState::name()
{
	return "AirborneState";
}
