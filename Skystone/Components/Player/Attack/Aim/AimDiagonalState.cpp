#include "AimDiagonalState.h"

#include "Components/Player/PlayerControlComponent.h"

AimDiagonalState::AimDiagonalState(GameObject& owner)
	: PlayerAimState(owner),
	controlComponent_(nullptr)
{
}


AimDiagonalState::~AimDiagonalState()
{
}

void AimDiagonalState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyUp(e, UP))
	{
		controlComponent_->changeAttackState(scene, "DefaultAimState");
	}
	else if (GameInputs::keyUp(e, LEFT) && controlComponent_->isFacing(FacingDirection::LEFT))
	{
		controlComponent_->changeAttackState(scene, "AimUpState");
	}
	else if (GameInputs::keyUp(e, RIGHT) && controlComponent_->isFacing(FacingDirection::RIGHT))
	{
		controlComponent_->changeAttackState(scene, "AimUpState");
	}
}

void AimDiagonalState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
}

void AimDiagonalState::update(Scene& scene)
{
}

double AimDiagonalState::getAngle()
{
	switch (controlComponent_->getFacingDirection())
	{
	case FacingDirection::LEFT:
		return 225;
	case FacingDirection::RIGHT:
		return 315;
	default:
		__debugbreak();
		return 0;
	}
}

std::string AimDiagonalState::name()
{
	return "AimDiagonalState";
}
