#include "DefaultAimState.h"

#include "Game/GameInputs.h"
#include "PlayerAttackState.h"
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
	//renderer_->setSprite()
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
	else if (GameInputs::keyDown(e, UP))
	{
		controlComponent_->changeAttackState(scene, "AimUpState");
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
	return facingRight_ ? 0 : 180;
}

std::string DefaultAimState::name()
{
	return "DefaultAimState";
}
