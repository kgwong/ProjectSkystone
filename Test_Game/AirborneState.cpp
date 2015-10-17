#include "AirborneState.h"

#include "Player.h"
#include "TestPlayerStates.h"	

AirborneState::AirborneState()
{
}


AirborneState::~AirborneState()
{
}

void AirborneState::onEnter(Player& player)
{
	jumpHeld_ = true;
}

void AirborneState::onExit(Player& player)
{
}

void AirborneState::handleInput(Player& player, SDL_Event& e)
{
	if (!jumpHeld_)
	{
		if (e.key.keysym.sym == controlMap[JUMP])
			player.changeState(&states::flyingState);
	}
}

void AirborneState::update(Player& player)
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
		player.getComponent<PhysicsComponent>()->setVelX(-5);
	}
	if (keyStates[SDL_GetScancodeFromKey(controlMap[RIGHT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(5);
	}

	if (!keyStates[SDL_GetScancodeFromKey(controlMap[JUMP])])
	{
		jumpHeld_ = false;
	}
}