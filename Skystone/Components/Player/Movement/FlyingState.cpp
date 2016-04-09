#include "FlyingState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Render/SpriteRenderer.h"
#include "Resources/Resources.h"

const float FlyingState::FLIGHT_VELOCITY = 5 * 60.0f;

FlyingState::FlyingState()
{
}


FlyingState::~FlyingState()
{
}

void FlyingState::onEnter(Scene& scene, GameObject& player)
{
	player.getComponent<PhysicsComponent>()->setVelY(-FLIGHT_VELOCITY);
	player.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/jetcycle.png"));
}

void FlyingState::onExit(Scene& scene, GameObject& player)
{
}

void FlyingState::handleInput(Scene& scene, GameObject& player, SDL_Event& e)
{
	if (GameInputs::keyUp(e, JUMP))
	{
		//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::airborneState);
		player.getComponent<PlayerControlComponent>()->changeMovementState(scene, &PlayerMovementState::airborneState);
	}
}

void FlyingState::update(Scene& scene, GameObject& player)
{
	if (!player.getComponent<PhysicsComponent>()->isFalling())
	{
		//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::walkingState);
		player.getComponent<PlayerControlComponent>()->changeMovementState(scene, &PlayerMovementState::walkingState);
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
