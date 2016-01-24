#include "WalkingState.h"

#include "GameObject.h"
#include "PlayerMovementState.h"
#include "PlayerControlComponent.h"

#include "Components\Render\SpriteRenderer.h"

WalkingState::WalkingState()
{
}

WalkingState::~WalkingState()
{
}

void WalkingState::onEnter(GameObject& player)
{
}

void WalkingState::onExit(GameObject& player)
{
}

void WalkingState::handleInput(GameObject& player, SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == controlMap[JUMP])
		{
			player.getComponent<PhysicsComponent>()->setVelY(JUMP_VELOCITY);
		}

	}
}

void WalkingState::update(GameObject& player)
{
	if (player.getComponent<PhysicsComponent>()->isFalling())
	{
		//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::airborneState);
		player.getComponent<PlayerControlComponent>()->changeMovementState(&PlayerMovementState::airborneState);

		return;
	}

	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	player.getComponent<PhysicsComponent>()->setVelX(0);

	if (keyStates[SDL_GetScancodeFromKey(controlMap[LEFT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(-WALK_VELOCITY);
		player.getComponent<SpriteRenderer>()->setFlipHorz(true);
		//player.getComponent<SpriteRenderer>()->flip(Axis::X);
	}
	if (keyStates[SDL_GetScancodeFromKey(controlMap[RIGHT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(WALK_VELOCITY);
		player.getComponent<SpriteRenderer>()->setFlipHorz(false);
	//	player.getComponent<SpriteRenderer>()->flip(Axis::X);
	}
}
