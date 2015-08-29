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
	player.getComponent<PhysicsComponent>()->setVelY(-5);
}

void FlyingState::onExit(Player& player)
{
}

void FlyingState::handleInput(Player& player, SDL_Event& e)
{
	if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_a)
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

	if (keyStates[SDL_SCANCODE_LEFT])
	{
		player.getComponent<PhysicsComponent>()->setVelX(-5);
	}
	if (keyStates[SDL_SCANCODE_RIGHT])
	{
		player.getComponent<PhysicsComponent>()->setVelX(5);
	}
	if (keyStates[SDL_SCANCODE_A])
	{
		player.getComponent<PhysicsComponent>()->setVelY(0);
	}
	if (keyStates[SDL_SCANCODE_UP])
	{
		player.getComponent<PhysicsComponent>()->setVelY(-5);
	}

	if (keyStates[SDL_SCANCODE_DOWN])
	{
		player.getComponent<PhysicsComponent>()->setVelY(5);
	}
}
