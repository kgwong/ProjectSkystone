#include "DefaultAimState.h"

#include "Game/GameInputs.h"
#include "PlayerAttackState.h"
#include "Components/Player/PlayerControlComponent.h"

DefaultAimState::DefaultAimState()
	:facingRight_(true)
{
}


DefaultAimState::~DefaultAimState()
{
}

void DefaultAimState::onEnter(GameObject& player)
{
}

void DefaultAimState::onExit(GameObject& player)
{
}

void DefaultAimState::handleInput(GameObject& player, SDL_Event& e)
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
		//player.getComponent<PlayerAttackState>()->changeState(&PlayerAttackState::aimUpState);
		player.getComponent<PlayerControlComponent>()->changeAttackState(&PlayerAttackState::aimUpState);
	}
}

void DefaultAimState::update(GameObject& player)
{
}

double DefaultAimState::getAngle()
{
	return facingRight_ ? 0 : 180;
}

std::string DefaultAimState::name()
{
	return "Default Aim State";
}
