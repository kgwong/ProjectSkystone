#include "WalkingState.h"

#include "GameObject/GameObject.h"
#include "PlayerMovementState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Application/Log.h"

const float WalkingState::JUMP_VELOCITY = -1200;
const float WalkingState::WALK_VELOCITY = 300;

WalkingState::WalkingState(GameObject& owner)
	:PlayerState(owner),
	controlComponent_(nullptr),
	physics_(nullptr)
{
}

WalkingState::~WalkingState()
{
}

void WalkingState::onEnter(Scene& scene)
{
}

void WalkingState::onExit(Scene& scene)
{
}

void WalkingState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyUp(e, LEFT) && controlComponent_->isFacing(FacingDirection::LEFT))
	{
		controlComponent_->changeMovementState(scene, "IdleState");
	}
	else if (GameInputs::keyUp(e, RIGHT) && controlComponent_->isFacing(FacingDirection::RIGHT))
	{
		controlComponent_->changeMovementState(scene, "IdleState");
	}
	else if (GameInputs::keyDown(e, JUMP))
	{
		physics_->setVelY(JUMP_VELOCITY);
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
	if (GameInputs::keyHeld(LEFT))
	{
		physics_->setVelX(-WALK_VELOCITY);
	}
	else if (GameInputs::keyHeld(RIGHT))
	{
		physics_->setVelX(WALK_VELOCITY);
	}
}

std::string WalkingState::name()
{
	return "WalkingState";
}
