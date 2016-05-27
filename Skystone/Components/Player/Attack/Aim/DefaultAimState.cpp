#include "DefaultAimState.h"

#include "Game/GameInputs.h"
#include "../PlayerAttackState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Render/SpriteRenderer.h"
#include "Components/Render/SpriteAnimator.h"

#include "Components/Player/Movement/WalkingState.h"

DefaultAimState::DefaultAimState(GameObject& owner)
	: PlayerAimState(owner),
	controlComponent_(nullptr)
{
}


DefaultAimState::~DefaultAimState()
{
}

void DefaultAimState::onEnter(Scene& scene)
{
}

void DefaultAimState::handleInput(Scene& scene, SDL_Event& e)
{
	if (GameInputs::keyDown(e, RIGHT))
	{
		controlComponent_->setFacingDirection(FacingDirection::RIGHT);
	}
	else if (GameInputs::keyDown(e, LEFT))
	{
		controlComponent_->setFacingDirection(FacingDirection::LEFT);
	}
	else if (GameInputs::keyDown(e, UP))
	{
		if (GameInputs::keyHeld(LEFT) || GameInputs::keyHeld(RIGHT))
		{
			controlComponent_->changeAttackState(scene, "AimDiagonalState");
		}
		else
		{
			controlComponent_->changeAttackState(scene, "AimUpState");
		}
	}
}

void DefaultAimState::start(Scene& scene)
{
	controlComponent_ = owner_.getComponent<PlayerControlComponent>();	
}

void DefaultAimState::update(Scene& scene)
{
}

double DefaultAimState::getAngle()
{
	switch (controlComponent_->getFacingDirection())
	{
	case FacingDirection::LEFT:
		return 180;
	case FacingDirection::RIGHT:
		return 0;
	default:
		__debugbreak();
		return 0;
	}
}

std::string DefaultAimState::name()
{
	return "DefaultAimState";
}
