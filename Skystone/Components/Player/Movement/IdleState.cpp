#include "IdleState.h"

#include "Components/Player/PlayerControlComponent.h"
#include "Components/Physics/PhysicsComponent.h"

#include "WalkingState.h"

IdleState::IdleState(GameObject& owner)
	: PlayerState(owner),
	controlComponent_(nullptr),
	physics_(nullptr)
{
}


IdleState::~IdleState()
{
}

void IdleState::onEnter(Scene& scene)
{
	if (GameInputs::keyHeld(LEFT) || GameInputs::keyHeld(RIGHT))
	{
		controlComponent_->changeMovementState(scene, "WalkingState");
		return;
	}
	physics_->setVelX(0);
}

void IdleState::onExit(Scene& scene)
{
}

void IdleState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyDown(e, LEFT))
	{
		controlComponent_->setFacingDirection(FacingDirection::LEFT);
		controlComponent_->changeMovementState(scene, "WalkingState");
	}
	else if (GameInputs::keyDown(e, RIGHT))
	{
		controlComponent_->setFacingDirection(FacingDirection::RIGHT);
		controlComponent_->changeMovementState(scene, "WalkingState");
	}
	else if (GameInputs::keyDown(e, JUMP))
	{
		physics_->setVelY(WalkingState::JUMP_VELOCITY);
	}
	else if (GameInputs::keyHeld(UP))
	{
		controlComponent_->changeMovementState(scene, "LockMovementState");
	}
	else if (GameInputs::keyDown(e, DOWN))
	{
		controlComponent_->changeMovementState(scene, "CrouchState");
	}
}

void IdleState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
	physics_ = owner_.getComponent<PhysicsComponent>();
}

void IdleState::update(Scene& scene)
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
}

std::string IdleState::name()
{
	return "IdleState";
}
