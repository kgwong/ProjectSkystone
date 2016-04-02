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

void WalkingState::onEnter(Scene& scene, GameObject& player)
{
	player.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/idle cycle.png"));
}

void WalkingState::onExit(Scene& scene, GameObject& player)
{
}

void WalkingState::handleInput(Scene& scene, GameObject& player, SDL_Event& e)
{
	if (GameInputs::keyDown(e, JUMP))
	{
		player.getComponent<PhysicsComponent>()->setVelY(JUMP_VELOCITY);
	}
}

void WalkingState::update(Scene& scene, GameObject& player)
{
	if (player.getComponent<PlayerControlComponent>()->HookState().getState() == &PlayerHookState::connectState)
	{
		player.getComponent<PlayerControlComponent>()->changeMovementState(scene, &PlayerMovementState::hangState);
	}

	if (player.getComponent<PhysicsComponent>()->isFalling())
	{
		//player.getComponent<PlayerMovementState>()->changeState(&PlayerMovementState::airborneState);
		player.getComponent<PlayerControlComponent>()->changeMovementState(scene, &PlayerMovementState::airborneState);
		return;
	}

	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	player.getComponent<PhysicsComponent>()->setVelX(0);

	if (GameInputs::keyHeld(LEFT))
	{
		player.getComponent<PhysicsComponent>()->setVelX(-WALK_VELOCITY);
		player.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/run_cycle.png"));
		player.getComponent<SpriteRenderer>()->setFlipHorz(true);
		//player.getComponent<SpriteRenderer>()->flip(Axis::X);
	}
	else if (GameInputs::keyHeld(RIGHT))
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
