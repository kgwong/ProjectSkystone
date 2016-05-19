#include "WalkingState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"

#include "Components/Render/SpriteAnimator.h"

const float WalkingState::JUMP_VELOCITY = -1200;
const float WalkingState::WALK_VELOCITY = 300;

WalkingState::WalkingState(GameObject& owner)
	:PlayerState(owner),
	subState_(SubState::IDLE),
	controlComponent_(nullptr),
	physics_(nullptr),
	animator_(nullptr)
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
		physics_->setVelY(JUMP_VELOCITY);
	}
	else if (GameInputs::keyHeld(UP) && subState_ == SubState::IDLE)
	{
		controlComponent_->changeMovementState(scene, "LockMovementState");
	}
	else if (GameInputs::keyDown(e, DOWN))
	{
		controlComponent_->changeMovementState(scene, "CrouchState");
	}
}

void WalkingState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
	animator_ = owner_.getComponent<SpriteAnimator>();
}

void WalkingState::update(Scene& scene)
{
	if (controlComponent_->HookState().getState()->name() == "HookConnectState")
	{
		controlComponent_->changeMovementState(scene, "Hang");
	}

	if (physics_->isFalling())
	{
		controlComponent_->changeMovementState(scene, "AirborneState");
		return;
	}

	physics_->setVelX(0);

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
		physics_->setVelX(-WALK_VELOCITY);
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
		physics_->setVelX(WALK_VELOCITY);
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
		animator_->setSpriteSheet("Images/idle cycle.png");
		break;
	case SubState::LEFT:
		animator_->setSpriteSheet("Images/run_cycle.png");
		animator_->setFlipHorz(true);
		break;
	case SubState::RIGHT:
		animator_->setSpriteSheet("Images/run_cycle.png");
		animator_->setFlipHorz(false);
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

