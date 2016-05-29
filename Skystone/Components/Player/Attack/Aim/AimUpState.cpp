#include "AimUpState.h"

#include "Game/GameInputs.h"
#include "Components/Player/PlayerControlComponent.h"

AimUpState::AimUpState(GameObject& owner)
	: PlayerAimState(owner)
{
}


AimUpState::~AimUpState()
{
}

void AimUpState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyDown(e, RIGHT))
	{
		controlComponent_->setFacingDirection(FacingDirection::RIGHT);
		controlComponent_->changeAttackState(scene, "AimDiagonalState");
	}
	else if (GameInputs::keyDown(e, LEFT))
	{
		controlComponent_->setFacingDirection(FacingDirection::LEFT);
		controlComponent_->changeAttackState(scene, "AimDiagonalState");
	}
	else if (GameInputs::keyUp(e, UP))
	{
		controlComponent_->changeAttackState(scene, "DefaultAimState");
	}
}

void AimUpState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();
}

void AimUpState::update(Scene& scene)
{
}

double AimUpState::getAngle()
{
	return 270;
}

std::string AimUpState::name()
{
	return "AimUpState";
}
