#include "FlyingState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"

const float FlyingState::FLIGHT_VELOCITY = 5 * 60.0f;

FlyingState::FlyingState()
{
}


FlyingState::~FlyingState()
{
}

void FlyingState::onEnter(GameObject& player)
{
	player.getComponent<PhysicsComponent>()->setVelY(-FLIGHT_VELOCITY);
}

void FlyingState::onExit(GameObject& player)
{
}

void FlyingState::handleInput(GameObject& player, SDL_Event& e)
{
	if (GameInputs::keyUp(e, JUMP))
	{
		//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::airborneState);
		player.getComponent<PlayerControlComponent>()->changeMovementState(&PlayerMovementState::airborneState);
	}
}

void FlyingState::update(GameObject& player)
{
	if (!player.getComponent<PhysicsComponent>()->isFalling())
	{
		//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::walkingState);
		player.getComponent<PlayerControlComponent>()->changeMovementState(&PlayerMovementState::walkingState);
		return;
	}
	player.getComponent<PhysicsComponent>()->setVelX(0);

	if (GameInputs::keyHeld(LEFT))
	{
		player.getComponent<PhysicsComponent>()->setVelX(-FLIGHT_VELOCITY);
	}
	if (GameInputs::keyHeld(RIGHT))
	{
		player.getComponent<PhysicsComponent>()->setVelX(FLIGHT_VELOCITY);
	}
	if (GameInputs::keyHeld(JUMP))
	{
		player.getComponent<PhysicsComponent>()->setVelY(0);
	}
	if (GameInputs::keyHeld(UP))
	{
		player.getComponent<PhysicsComponent>()->setVelY(-FLIGHT_VELOCITY);
	}
	if (GameInputs::keyHeld(DOWN))
	{
		player.getComponent<PhysicsComponent>()->setVelY(FLIGHT_VELOCITY);
	}
}
