#include "FlyingState.h"

#include "GameObject.h"
#include "PlayerMovementState.h"
#include "PlayerControlComponent.h"

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
	if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[JUMP])
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
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	player.getComponent<PhysicsComponent>()->setVelX(0);

	if (keyStates[SDL_GetScancodeFromKey(controlMap[LEFT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(-FLIGHT_VELOCITY);
	}
	if (keyStates[SDL_GetScancodeFromKey(controlMap[RIGHT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(FLIGHT_VELOCITY);
	}
	if (keyStates[SDL_GetScancodeFromKey(controlMap[JUMP])])
	{
		player.getComponent<PhysicsComponent>()->setVelY(0);
	}
	if (keyStates[SDL_GetScancodeFromKey(controlMap[UP])])
	{
		player.getComponent<PhysicsComponent>()->setVelY(-FLIGHT_VELOCITY);
	}
	if (keyStates[SDL_GetScancodeFromKey(controlMap[DOWN])])
	{
		player.getComponent<PhysicsComponent>()->setVelY(FLIGHT_VELOCITY);
	}
}
