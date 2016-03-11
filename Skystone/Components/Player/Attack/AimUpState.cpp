#include "AimUpState.h"

#include "PlayerAttackState.h"
#include "Components/Physics/PhysicsComponent.h"
#include "Components/Player/PlayerControlComponent.h"

#include "Application/Log.h"

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
	if (GameInputs::keyUp(e, UP))
	{
		//player.getComponent<PlayerAttackState>()->changeState(&PlayerAttackState::defaultAimState);
		player.getComponent<PlayerControlComponent>()->changeAttackState(&PlayerAttackState::defaultAimState);
	}
	if (GameInputs::keyDown(e, LEFT))
	{
		dir_ = AimUpState::Direction::LEFT;
	}
	if (GameInputs::keyUp(e, LEFT))
	{
		dir_ = AimUpState::Direction::NONE;
	}
	if (GameInputs::keyDown(e, RIGHT))
	{
		dir_ = AimUpState::Direction::RIGHT;
	}
	if (GameInputs::keyUp(e, RIGHT))
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
