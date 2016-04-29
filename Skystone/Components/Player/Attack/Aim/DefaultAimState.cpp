#include "DefaultAimState.h"

#include "Game/GameInputs.h"
#include "../PlayerAttackState.h"
#include "Components/Player/PlayerControlComponent.h"
#include "Components/Render/SpriteRenderer.h"

DefaultAimState::DefaultAimState(GameObject& owner)
	: PlayerAimState(owner),
	facingRight_(true)
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
		facingRight_ = true;
	}
	else if (GameInputs::keyDown(e, LEFT))
	{
		facingRight_ = false;
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
	if (GameInputs::keyHeld(UP))
	{
		if (GameInputs::keyHeld(LEFT))
		{
			return 225;
		}
		else if (GameInputs::keyHeld(RIGHT))
		{
			return 315;
		}
		else
		{
			return 270;
		}
	}
	else
	{
		return facingRight_ ? 0 : 180;
	}
}

std::string DefaultAimState::name()
{
	return "DefaultAimState";
}
