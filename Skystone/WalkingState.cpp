#include "WalkingState.h"

#include "Player.h"
#include "TestPlayerStates.h"

WalkingState::WalkingState()
{
}

WalkingState::~WalkingState()
{
}

void WalkingState::onEnter(Player& player)
{
}

void WalkingState::onExit(Player& player)
{
}

void WalkingState::handleInput(Player& player, SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == controlMap[JUMP])
			player.getComponent<PhysicsComponent>()->setVelY(Player::JUMP_VELOCITY);

	}
}

void WalkingState::update(Player& player)
{
	if (player.getComponent<PhysicsComponent>()->isFalling())
	{
		player.changeState(&states::airborneState);
		return;
	}

	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	player.getComponent<PhysicsComponent>()->setVelX(0);

	if (keyStates[SDL_GetScancodeFromKey(controlMap[LEFT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(-Player::WALK_VELOCITY);
	}
	if (keyStates[SDL_GetScancodeFromKey(controlMap[RIGHT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(Player::WALK_VELOCITY);
	}
}
