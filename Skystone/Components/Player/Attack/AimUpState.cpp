#include "AimUpState.h"

#include "PlayerAttackState.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Player/PlayerControlComponent.h"

#include "Log.h"

AimUpState::AimUpState()
{
}


AimUpState::~AimUpState()
{
}

void AimUpState::onEnter(GameObject & player)
{
	dir_ = AimUpState::Direction::NONE;
}

void AimUpState::handleInput(GameObject& player, SDL_Event& e)
{
	if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[UP])
	{
		//player.getComponent<PlayerAttackState>()->changeState(&PlayerAttackState::defaultAimState);
		player.getComponent<PlayerControlComponent>()->changeAttackState(&PlayerAttackState::defaultAimState);
	}
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[LEFT])
	{
		dir_ = AimUpState::Direction::LEFT;
	}
	if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[LEFT])
	{
		dir_ = AimUpState::Direction::NONE;
	}
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == controlMap[RIGHT])
	{
		dir_ = AimUpState::Direction::RIGHT;
	}
	if (e.type == SDL_KEYUP && e.key.keysym.sym == controlMap[RIGHT])
	{
		dir_ = AimUpState::Direction::NONE;
	}

}

void AimUpState::update(GameObject& player)
{
	if (dir_ != AimUpState::Direction::NONE)
	{
		player.getComponent<PhysicsComponent>()->setVelX(0);
	}
}

double AimUpState::getAngle()
{
	switch (dir_)
	{
	case AimUpState::Direction::LEFT:
		return 225;
	case AimUpState::Direction::RIGHT:
		return 315;
	default:
		return 270;
	}
}

std::string AimUpState::name()
{
	return "Aim Up State";
}
