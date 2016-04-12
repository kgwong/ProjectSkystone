#include "FlyingState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Render/SpriteRenderer.h"
#include "Resources/Resources.h"

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
	owner_.getComponent<PhysicsComponent>()->setVelY(-FLIGHT_VELOCITY);
	owner_.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/jetcycle.png"));
}

void FlyingState::onExit(Scene& scene)
{
}

void FlyingState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyUp(e, JUMP))
	{
		//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::airborneState);
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
	}
}

void FlyingState::update(Scene& scene)
{
	if (!owner_.getComponent<PhysicsComponent>()->isFalling())
	{
		//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::walkingState);
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "WalkingState");
		return;
	}
	owner_.getComponent<PhysicsComponent>()->setVelX(0);

	if (GameInputs::keyHeld(LEFT))
	{
		owner_.getComponent<PhysicsComponent>()->setVelX(-FLIGHT_VELOCITY);
	}
	if (GameInputs::keyHeld(RIGHT))
	{
		owner_.getComponent<PhysicsComponent>()->setVelX(FLIGHT_VELOCITY);
	}
	if (GameInputs::keyHeld(JUMP))
	{
		owner_.getComponent<PhysicsComponent>()->setVelY(0);
	}
	if (GameInputs::keyHeld(UP))
	{
		owner_.getComponent<PhysicsComponent>()->setVelY(-FLIGHT_VELOCITY);
	}
	if (GameInputs::keyHeld(DOWN))
	{
		owner_.getComponent<PhysicsComponent>()->setVelY(FLIGHT_VELOCITY);
	}
}
