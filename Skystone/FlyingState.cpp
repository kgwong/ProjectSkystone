#include "FlyingState.h"

#include "Player.h"
#include "TestPlayerStates.h"

FlyingState::FlyingState()
{
}


FlyingState::~FlyingState()
{
}

void FlyingState::onEnter(Player& player)
{
	player.getComponent<PhysicsComponent>()->setVelY(-Player::FLIGHT_VELOCITY);
}

void FlyingState::onExit(Player& player)
{
}

void FlyingState::handleInput(Player& player, SDL_Event& e)
{
	if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[JUMP])
		player.changeState(&states::airborneState);
}

void FlyingState::update(Player& player)
{
	if (!player.getComponent<PhysicsComponent>()->isFalling())
	{
		player.changeState(&states::walkingState);
		return;
	}
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	player.getComponent<PhysicsComponent>()->setVelX(0);

	if (keyStates[SDL_GetScancodeFromKey(controlMap[LEFT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(-Player::FLIGHT_VELOCITY);
	}
	if (keyStates[SDL_GetScancodeFromKey(controlMap[RIGHT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(Player::FLIGHT_VELOCITY);
	}
	if (keyStates[SDL_GetScancodeFromKey(controlMap[JUMP])])
	{
		player.getComponent<PhysicsComponent>()->setVelY(0);
	}
	if (keyStates[SDL_GetScancodeFromKey(controlMap[UP])])
	{
		player.getComponent<PhysicsComponent>()->setVelY(-Player::FLIGHT_VELOCITY);
	}
	if (keyStates[SDL_GetScancodeFromKey(controlMap[DOWN])])
	{
		player.getComponent<PhysicsComponent>()->setVelY(Player::FLIGHT_VELOCITY);
	}
}
