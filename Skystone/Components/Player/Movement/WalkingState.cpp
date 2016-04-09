#include "WalkingState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"

#include "Components/Render/SpriteRenderer.h"

#include "Resources/Resources.h"


const float WalkingState::JUMP_VELOCITY = -1200;
const float WalkingState::WALK_VELOCITY = 300;

WalkingState::SubState WalkingState::subState_ = SubState::IDLE;

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
		player.getComponent<PlayerControlComponent>()->changeMovementState(scene, &PlayerMovementState::airborneState);
		return;
	}

	player.getComponent<PhysicsComponent>()->setVelX(0);

	switch (subState_)
	{
	case SubState::IDLE:
		if (GameInputs::keyHeld(LEFT))
		{
			changeSubState(player, SubState::LEFT);
		}
		else if (GameInputs::keyHeld(RIGHT))
		{
			changeSubState(player, SubState::RIGHT);
		}
		else
		{

		}
		break;
	case SubState::LEFT:
		player.getComponent<PhysicsComponent>()->setVelX(-WALK_VELOCITY);
		if (GameInputs::keyHeld(LEFT))
		{

		}
		else if (GameInputs::keyHeld(RIGHT))
		{
			changeSubState(player, SubState::RIGHT);
		}
		else
		{
			changeSubState(player, SubState::IDLE);
		}
		break;
	case SubState::RIGHT:
		player.getComponent<PhysicsComponent>()->setVelX(WALK_VELOCITY);
		if (GameInputs::keyHeld(LEFT))
		{
			changeSubState(player, SubState::LEFT);
		}
		else if (GameInputs::keyHeld(RIGHT))
		{

		}
		else
		{
			changeSubState(player, SubState::IDLE);
		}
	}

}

void WalkingState::changeSubState(GameObject& player, SubState newSubState)
{
	subState_ = newSubState;
	switch (newSubState)
	{
	case SubState::IDLE:
		player.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/idle cycle.png"));
		break;
	case SubState::LEFT:
		player.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/run_cycle.png"));
		player.getComponent<SpriteRenderer>()->setFlipHorz(true);
		break;
	case SubState::RIGHT:
		player.getComponent<SpriteRenderer>()->setSprite(Resources::getSpriteSheet("Images/run_cycle.png"));
		player.getComponent<SpriteRenderer>()->setFlipHorz(false);
		break;
	}
}

std::string WalkingState::subStateToString(SubState subState)
{
	switch (subState)
	{
	case SubState::IDLE:
		return "IDLE";
	case SubState::LEFT:
		return "LEFT";
	case SubState::RIGHT:
		return "RIGHT";
	default:
		return "ERROR";
	}
}

