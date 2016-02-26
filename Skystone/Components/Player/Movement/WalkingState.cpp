#include "WalkingState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"

#include "Components/Render/SpriteRenderer.h"

#include "Resources/Resources.h"

const float WalkingState::JUMP_VELOCITY = -1200;
const float WalkingState::WALK_VELOCITY = 300;

WalkingState::WalkingState()
{
}

WalkingState::~WalkingState()
{
}

void WalkingState::onEnter(GameObject& player)
{
	player.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/idle cycle.png"));
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
		player.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/run_cycle.png"));
		player.getComponent<SpriteRenderer>()->setFlipHorz(true);
		//player.getComponent<SpriteRenderer>()->flip(Axis::X);
	}
	else if (keyStates[SDL_GetScancodeFromKey(controlMap[RIGHT])])
	{
		player.getComponent<PhysicsComponent>()->setVelX(WALK_VELOCITY);
		player.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/run_cycle.png"));
		player.getComponent<SpriteRenderer>()->setFlipHorz(false);
	//	player.getComponent<SpriteRenderer>()->flip(Axis::X);
	}
	else
	{
		player.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/idle cycle.png"));
	}
}
