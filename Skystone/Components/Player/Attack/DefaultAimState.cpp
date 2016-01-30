#include "DefaultAimState.h"

#include "Game/Controls.h"
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
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[RIGHT])
	{
		facingRight_ = true;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[LEFT])
	{
		facingRight_ = false;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[UP])
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
