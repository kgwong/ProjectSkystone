#include "AirborneState.h"

#include "GameObject.h"
#include "PlayerMovementState.h"
//#include "TestPlayerStates.h"	

AirborneState::AirborneState()
{
}


AirborneState::~AirborneState()
{
}

void AirborneState::onEnter(GameObject& player)
{
	jumpHeld_ = true;
}

void AirborneState::onExit(GameObject& player)
{
}

void AirborneState::handleInput(GameObject& player, SDL_Event& e)
{
	if (!jumpHeld_)
	{
		if (e.key.keysym.sym == controlMap[JUMP])
			player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::flyingState);
	}
}

void AirborneState::update(GameObject& player)
{
	if (!player.getComponent<PhysicsComponent>()->isFalling())
	{
		player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::walkingState);
		return;
	}
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	if (keyStates[SDL_GetScancodeFromKey(controlMap[LEFT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(-5);
	}
	else if (keyStates[SDL_GetScancodeFromKey(controlMap[RIGHT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(5);
	}
	else
	{
		player.getComponent<PhysicsComponent>()->setVelX(0);
	}

	if (!keyStates[SDL_GetScancodeFromKey(controlMap[JUMP])])
	{
		jumpHeld_ = false;
	}
}