#include "WalkingState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"

#include "Components/Render/SpriteRenderer.h"

const float WalkingState::JUMP_VELOCITY = -1200;
const float WalkingState::WALK_VELOCITY = 300;

WalkingState::SubState WalkingState::subState_ = SubState::IDLE;

WalkingState::WalkingState(GameObject& owner)
	:PlayerState(owner)
{
}

WalkingState::~WalkingState()
{
}

void WalkingState::onEnter(Scene& scene)
{
	changeSubState(subState_);
}

void WalkingState::onExit(Scene& scene)
{
}

void WalkingState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyDown(e, JUMP))
	{
		owner_.getComponent<PhysicsComponent>()->setVelY(JUMP_VELOCITY);
	}
}

void WalkingState::update(Scene& scene)
{
	if (owner_.getComponent<PlayerControlComponent>()->HookState().getState()->name() == "HookConnectState")
	{
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "Hang");
	}

	if (owner_.getComponent<PhysicsComponent>()->isFalling())
	{
		owner_.getComponent<PlayerControlComponent>()->changeMovementState(scene, "AirborneState");
		return;
	}

	owner_.getComponent<PhysicsComponent>()->setVelX(0);

	switch (subState_)
	{
	case SubState::IDLE:
		if (GameInputs::keyHeld(LEFT))
		{
			changeSubState(SubState::LEFT);
		}
		else if (GameInputs::keyHeld(RIGHT))
		{
			changeSubState(SubState::RIGHT);
		}
		else
		{

		}
		break;
	case SubState::LEFT:
		owner_.getComponent<PhysicsComponent>()->setVelX(-WALK_VELOCITY);
		if (GameInputs::keyHeld(LEFT))
		{

		}
		else if (GameInputs::keyHeld(RIGHT))
		{
			changeSubState(SubState::RIGHT);
		}
		else
		{
			changeSubState(SubState::IDLE);
		}
		break;
	case SubState::RIGHT:
		owner_.getComponent<PhysicsComponent>()->setVelX(WALK_VELOCITY);
		if (GameInputs::keyHeld(LEFT))
		{
			changeSubState(SubState::LEFT);
		}
		else if (GameInputs::keyHeld(RIGHT))
		{

		}
		else
		{
			changeSubState(SubState::IDLE);
		}
	}

}

void WalkingState::changeSubState(SubState newSubState)
{
	subState_ = newSubState;
	switch (newSubState)
	{
	case SubState::IDLE:
		owner_.getComponent<SpriteRenderer>()->setSprite("Images/idle cycle.png");
		break;
	case SubState::LEFT:
		owner_.getComponent<SpriteRenderer>()->setSprite("Images/run_cycle.png");
		owner_.getComponent<SpriteRenderer>()->setFlipHorz(true);
		break;
	case SubState::RIGHT:
		owner_.getComponent<SpriteRenderer>()->setSprite("Images/run_cycle.png");
		owner_.getComponent<SpriteRenderer>()->setFlipHorz(false);
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

